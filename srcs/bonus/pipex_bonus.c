/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:29:52 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/08 20:07:33 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	ft_pipe_creation(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->commands_nb - 1)
	{
		if (pipe(vars->pipe + 2 * i) < 0)
			ft_free_parents(vars);
		i++;
	}
}

void	ft_pipe_close(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->pipes_nb)
		close(vars->pipe[i]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars) * 1);
	if (argc < ft_here_doc_arg(argv[1], vars))
		return (ft_message(errno, "Arguments: Invalid number.\n"));
	ft_infile(argv, vars);
	ft_outfile(argv[argc - 1], vars);
	vars->commands_nb = argc - 3 - vars->here_doc;
	vars->pipes_nb = 2 * (vars->commands_nb - 1);
	vars->pipe = (int *)malloc(sizeof(int) * vars->pipes_nb);
	if (!vars->pipe)
		ft_error(errno, "Mem reservation error.\n");
	vars->paths = ft_path_search(envp);
	vars->cmd_paths = ft_split(vars->paths, ':');
	if (!vars->cmd_paths)
		ft_free_mem(vars);
	ft_pipe_creation(vars);
	vars->index = -1;
	while (++vars->index < vars->commands_nb)
		ft_childs(vars, argv, envp);
	ft_pipe_close(vars);
	waitpid(-1, 0, 0);
	ft_free_parents(vars);
	free(vars);
	return (0);
}
