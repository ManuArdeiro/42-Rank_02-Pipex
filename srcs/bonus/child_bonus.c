/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:32:32 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/13 21:57:05 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

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

int	ft_count_parts(char *str, char c)
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

void	ft_double_dup(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	ft_childs(t_vars *vars, char **argv, char **envp)
{
	vars->pid = fork();
	if (vars->pid == 0)
	{
		if (vars->index == 0)
		{
			ft_double_dup(vars->infile, vars->pipe[1]);
			close(vars->pipe[0]);
		}
		else if (vars->index == vars->commands_nb - 1)
		{
			ft_double_dup(vars->pipe[2 * vars->index], vars->outfile);
			close(vars->pipe[2 * vars->index]);
			close(vars->pipe[2 * vars->index + 1]);
		}
		else
		{
			ft_double_dup(vars->pipe[2 * vars->index],
				vars->pipe[2 * vars->index + 1]);
			close(vars->pipe[2 * vars->index + 1]);
		}
		vars->cmd_args = ft_split(argv[2 + vars->here_doc + vars->index], ' ');
		vars->cmd = ft_cmd_const(vars->cmd_paths, vars->cmd_args[0]);
		if (!vars->cmd)
		{
			ft_error(1, vars->cmd_args[0]);
			ft_free_parents(vars);
			exit(1);
		}
		execve(vars->cmd, vars->cmd_args, envp);
	}
}
