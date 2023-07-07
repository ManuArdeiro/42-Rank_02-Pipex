/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:43:45 by bcaffere          #+#    #+#             */
/*   Updated: 2023/07/06 19:26:22 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*	Function to print an error message to the error output and return nb. */

int	ft_error_message(char *str_1, char *str_2, char *str_3, int nb)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str_1, 2);
	ft_putstr_fd(str_2, 2);
	ft_putstr_fd(str_3, 2);
	ft_putstr_fd("\n", 2);
	return (nb);
}


/*	Function to print an error message and exit (with 1). */

void	ft_error(int error_nb, char *error_text)
{
	perror(error_text);
	exit (error_nb);
}

/*	This function frees allocated memory (cmd_paths in struct vars)
	and closes the open files*/

void	ft_parent_free(t_vars *vars)
{
	int	i;
	
	i = 0;
	close(vars->infile);
	close(vars->outfile);
	while (vars->cmd_paths[i])
	{
		free(vars->cmd_paths[i]);
		i++;
	}
	free(vars->cmd_paths);
}

int	ft_init_vars(int argc, char **argv, char **envp, t_vars *vars)
{
	vars->pid_one = 0;
	vars->pid_two = 0;
	vars->infile = open(argv[1], O_RDONLY, 0644);
	if (vars->infile < 0) 
		return (ft_error_message(strerror(errno), ": ", (char *)argv[1], errno));
	vars->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (vars->outfile < 0) 
		return (ft_error_message(strerror(errno), ": ", (char *)argv[1], errno));
	if (pipe(vars->tube) < 0)
		return (ft_error_message("pipe", ": ", strerror(errno), errno));
	vars->paths = ft_path_search(envp);
	vars->cmd_paths = ft_split(vars->paths, ':');
	vars->cmd = 0;
	vars->cmd_args = 0;
	return (0);
}