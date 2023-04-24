/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:58:40 by bcaffere          #+#    #+#             */
/*   Updated: 2023/04/24 19:45:29 by jolopez-         ###   ########.fr       */
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
		if (access(complete, F_OK) == 0)
			return (complete);
		free(complete);
		paths++;
	}
	return (0);
}

void	ft_first_child(t_vars vars, char *argv[], char *envp[])
{
	int		i;
	char	*msg;

	i = -1;
	vars.infile = open(argv[1], O_RDONLY);
	if (vars.infile < 0)
		ft_message(EXIT_SUCCESS,
			ft_strjoin("no such file or directory: ", (char *)argv[1]));
	printf("%d\n", vars.tube[1]);
	close(vars.tube[0]);
	if (STDOUT_FILENO != vars.tube[1])
		if (dup2(vars.tube[1], STDOUT_FILENO) < 0)
			perror("Dup2");
	printf("aquí\n");
	dup2(vars.infile, STDIN_FILENO);
	close(vars.infile);
	printf("aquí\n");
	vars.cmd_args = ft_split(argv[2], ' ');
	printf("aquí\n");
	vars.cmd = ft_cmd_const(vars.cmd_paths, vars.cmd_args[0]);
	if (!vars.cmd)
	{
		msg = ft_strjoin("command not found: ", vars.cmd_args[0]); 
		ft_message(127, msg);
		free(msg);
		while (vars.cmd_args[++i])
			free(vars.cmd_args[i]);
		free(vars.cmd_args);
		free(vars.cmd);
		exit(127);
	}
	execve(vars.cmd, vars.cmd_args, envp);
}

void	ft_second_child(t_vars vars, int argc, char *argv[], char *envp[])
{
	int		i;
	char	*msg;

	i = -1;
	vars.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 00644);
	if (vars.outfile < 0)
		ft_message(EXIT_FAILURE, "21");
	dup2(vars.tube[0], STDIN_FILENO);
	close(vars.tube[1]);
	dup2(vars.outfile, STDOUT_FILENO);
	vars.cmd_args = ft_split(argv[3], ' ');
	vars.cmd = ft_cmd_const(vars.cmd_paths, vars.cmd_args[0]);
	if (!vars.cmd)
	{
		msg = ft_strjoin("command not found: ", vars.cmd_args[0]); 
		ft_message(127, msg);
		free(msg);
		while (vars.cmd_args[++i])
			free(vars.cmd_args[i]);
		free(vars.cmd_args);
		free(vars.cmd);
		exit (127);
	}
	execve(vars.cmd, vars.cmd_args, envp);
}
