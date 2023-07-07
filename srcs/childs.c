/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:58:40 by bcaffere          #+#    #+#             */
/*   Updated: 2023/07/06 18:30:43 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_cmd_const(char **paths, char *command)
{
	char	*path;
	char	*complete;

	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		complete = ft_strjoin(path, command);
		free(path);
		if (access(complete, X_OK) == 0)
			return (complete);
		free(complete);
		paths++;
	}
	return (0);
}

void	ft_first_child(t_vars vars, char *argv[], char *envp[])
{
	if (dup2(vars.infile, STDIN_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	if (dup2(vars.tube[1], STDOUT_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	vars.cmd_args = ft_split(argv[2], ' ');
	vars.cmd = ft_cmd_const(vars.cmd_paths, vars.cmd_args[0]);
	ft_close_pipes(&vars);
	close(vars.infile);
	close(vars.outfile);
	if (execve(vars.cmd, vars.cmd_args, envp) < 0)
		ft_error_message(vars.cmd, " : ", strerror(errno), 1);
}

void	ft_second_child(t_vars vars, int argc, char *argv[], char *envp[])
{
	if (dup2(vars.tube[0], STDIN_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	if (dup2(vars.outfile, STDOUT_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	vars.cmd_args = ft_split(argv[argc - 2], ' ');
	vars.cmd = ft_cmd_const(vars.cmd_paths, vars.cmd_args[0]);
	ft_close_pipes(&vars);
	close(vars.infile);
	close(vars.outfile);
	if (execve(vars.cmd, vars.cmd_args, envp) < 0)
		ft_error_message(vars.cmd, " : ", strerror(errno), 1);
}
