/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:58:39 by jolopez-          #+#    #+#             */
/*   Updated: 2023/04/18 19:55:50 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_path_search(char **envp)
{
	int	i;
	
	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		i++;
	return (envp[i] + 5);
}

void	ft_close_pipes(t_vars *vars)
{
	close(vars->tube[0]);
	close(vars->tube[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	if (argc != 5)
		return (ft_print_message("Arguments: Invalid number.\n"));
	vars.infile = open(argv[1], O_RDONLY);
	if (vars.infile < 0)
		ft_error("Arguments: Infile Error.\n");
	vars.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 00644);
	if (vars.outfile < 0)
		ft_error("Arguments: Outfile Error.\n");
	if (pipe(vars.tube) < 0)
		ft_error("Creating Pipe Error.\n");
	vars.paths = ft_path_search(envp);
	vars.cmd_paths = ft_split(vars.paths, ':');
	vars.pid1 = fork();
	if (vars.pid1 == 0)
		ft_first_child(vars, argv, envp);
	vars.pid2 = fork();
	if (vars.pid2 == 0)
		ft_second_child(vars, argv, envp);
	ft_close_pipes(&vars);
	waitpid(vars.pid1, 0, 0);
	waitpid(vars.pid2, 0, 0);
	ft_parent_free(&vars);
	return (0);
}
