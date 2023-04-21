/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:58:40 by bcaffere          #+#    #+#             */
/*   Updated: 2023/04/21 21:20:15 by jolopez-         ###   ########.fr       */
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
		if (access(complete, 0) == 0)
			return (complete);
		free(complete);
		paths++;
	}
	return (0);
}

void	ft_first_child(t_vars vars, char *argv[], char *envp[])
{
	int	i;

	i = -1;
	vars.infile = open(argv[1], O_RDONLY);
	if (vars.infile < 0)
		ft_message(EXIT_SUCCESS,
			ft_strjoin("no such file or directory: ", (char *)argv[1]));
	dup2(vars.tube[1], STDOUT_FILENO);
	close(vars.tube[0]);
	dup2(vars.infile, STDIN_FILENO);
	vars.cmd_args = ft_split(argv[2], ' ');
	vars.cmd = ft_cmd_const(vars.cmd_paths, vars.cmd_args[0]);
	if (!vars.cmd)
	{
		while (vars.cmd_args[++i])
			free(vars.cmd_args[i]);
		free(vars.cmd_args);
		free(vars.cmd);
		exit(ft_message(EXIT_SUCCESS,
				ft_strjoin("command not found: ", (char *)argv[1])));
	}
	execve(vars.cmd, vars.cmd_args, envp);
}

void	ft_second_child(t_vars vars, int argc, char *argv[], char *envp[])
{
	int	i;

	i = -1;
	vars.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 00644);
	if (vars.outfile < 0)
		ft_message(127, "21");
	dup2(vars.tube[0], STDIN_FILENO);
	close(vars.tube[1]);
	dup2(vars.outfile, STDOUT_FILENO);
	vars.cmd_args = ft_split(argv[3], ' ');
	vars.cmd = ft_cmd_const(vars.cmd_paths, vars.cmd_args[0]);
	if (!vars.cmd)
	{
		while (vars.cmd_args[++i])
			free(vars.cmd_args[i]);
		free(vars.cmd_args);
		free(vars.cmd);
		exit (ft_message(127,
				ft_strjoin("command not found: ", (char *)argv[argc - 1])));
	}
	execve(vars.cmd, vars.cmd_args, envp);
}
