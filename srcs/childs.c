/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:58:40 by bcaffere          #+#    #+#             */
/*   Updated: 2023/07/08 12:40:49 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*	Function to construct the command complete path	*/

char	*ft_cmd_const(char **paths, char *command)
{
	int		i;
	char	*path;
	char	*complete;
	char	**command_wo_path;

	command_wo_path = 0;
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		command_wo_path = ft_split(command, '/');
		i = ft_count_parts(command, '/') - 1;
		if (i < 0)
			i = 0;
		complete = ft_strjoin(path, command_wo_path[i]);
		free(path);
		if (access(complete, X_OK) == 0)
			return (complete);
		free(complete);
		paths++;
	}
	return (0);
}

/*	Function to count parts; it will be use to extract the command when it 
	is provided with complete path including directories */
	
int		ft_count_parts(char *str, char c)
{
	int	i;
	int	parts;

	parts = 0;
	i = 0;
	while (str)
	{
		while (str[i] != '\0')
		{
			if ((str[i + 1] == c || str[i + 1] == '\0')
				&& !(str[i] == c || str[i] == '\0'))
				parts++;
			i++;
		}
		return (parts);
	}
	return (0);
}

/*	First child function, it executes the first command of the pipe */

void	ft_first_child(t_vars *vars, char *argv[], char *envp[])
{
	if (dup2(vars->infile, STDIN_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	if (dup2(vars->tube[1], STDOUT_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	close(vars->tube[0]);
	close(vars->infile);
	close(vars->outfile);
	vars->cmd_args = ft_split(argv[2], ' ');
	vars->cmd = ft_cmd_const(vars->cmd_paths, vars->cmd_args[0]);
	if (access (vars->cmd, F_OK) != 0)
		exit(ft_error_message("command not found", ": ", vars->cmd_args[0], 127));
	if (execve(vars->cmd, vars->cmd_args, envp) < 0)
		ft_error_message(vars->cmd, " : ", strerror(errno), errno);
}

/*	Second child function, it executes the second command of the pipe */

void	ft_second_child(t_vars *vars, int argc, char *argv[], char *envp[])
{
	if (dup2(vars->tube[0], STDIN_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	if (dup2(vars->outfile, STDOUT_FILENO) < 0)
		ft_error(EXIT_FAILURE, "Dup2");
	close(vars->tube[1]);
	close(vars->infile);
	close(vars->outfile);
	vars->cmd_args = ft_split(argv[argc - 2], ' ');
	vars->cmd = ft_cmd_const(vars->cmd_paths, vars->cmd_args[0]);
	if (access (vars->cmd, F_OK) != 0)
		exit(ft_error_message("command not found", ": ", vars->cmd_args[0], 127));
	if (execve(vars->cmd, vars->cmd_args, envp) < 0)
		ft_error_message(vars->cmd, " : ", strerror(errno), errno);
}
