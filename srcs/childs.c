/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:58:40 by bcaffere          #+#    #+#             */
/*   Updated: 2023/06/12 19:42:43 by jolopez-         ###   ########.fr       */
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
	int		i;

	i = -1;
	close(vars.tube[1]);
	if (dup2(vars.infile, STDIN_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	if (dup2(vars.tube[0], STDOUT_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	vars.cmd_args = ft_split(argv[2], ' ');
	vars.cmd = ft_cmd_const(vars.cmd_paths, vars.cmd_args[0]);
	if (!vars.cmd)
	{
		ft_error_message("command not found", " : ", vars.cmd_args[0], 127);
		while (vars.cmd_args[++i])
			free(vars.cmd_args[i]);
		free(vars.cmd_args);
		free(vars.cmd);
		exit(127);
	}
	if (execve(vars.cmd, vars.cmd_args, envp) < 0)
		ft_error(ft_error_message(vars.cmd, " : ", strerror(errno), 1), "");
}

void	ft_second_child(t_vars vars, int argc, char *argv[], char *envp[])
{
	int		i;
	char	*str;

	i = -1;
	str = "";
	printf("Aquí. vars.tube[1] = %d \n", vars.tube[1]);
	if (dup2(vars.tube[1], STDIN_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	read(STDIN_FILENO, str, 1000);
	printf("str = %s \n", str);
	printf("Aquí. vars.outfile = %d \n", vars.outfile);
	if (dup2(vars.outfile, STDOUT_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	write(STDOUT_FILENO, "ok\n", 3);
	printf("Aquí.\n");
	close(vars.tube[0]);
	printf("Aquí.\n");
	vars.cmd_args = ft_split(argv[argc - 2], ' ');
	vars.cmd = ft_cmd_const(vars.cmd_paths, vars.cmd_args[0]);
	printf("vars.cmd = %s.\n", vars.cmd);
	if (!vars.cmd)
	{
		ft_error_message("command not found", " : ", vars.cmd_args[0], 127);
		while (vars.cmd_args[++i])
			free(vars.cmd_args[i]);
		free(vars.cmd_args);
		free(vars.cmd);
		exit(127);
	}
	printf("Aquí.\n");
	if (execve(vars.cmd, vars.cmd_args, envp) < 0)
		ft_error(ft_error_message(vars.cmd, " : ", strerror(errno), 1), "");
}
