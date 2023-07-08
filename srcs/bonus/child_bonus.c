/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:32:32 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/08 12:24:45 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

char	*ft_cmd_const(char **paths, char *cmd)
{
	char	*path;
	char	*complete;

	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		complete = ft_strjoin(path, cmd);
		free(path);
		if (access(complete, 0) == 0)
			return (complete);
		free(complete);
		paths++;
	}
	return (0);
}

void	ft_double_dup(int zero, int one)
{
	dup2(zero, 0);
	dup2(one, 1);


void	ft_childs(t_vars vars, char **argv, char **envp)
{
	vars.pid = fork();
	if (!vars.pid)
	{
		if (vars.index == 0)
			ft_double_dup(vars.infile, vars.pipe[1]);
		else if (vars.index == vars.commands_nb - 1)
			ft_double_dup(vars.pipe[2 * vars.index - 2], vars.outfile);
		else
			ft_double_dup(vars.pipe[2 * vars.index - 2],
				vars.pipe[2 * vars.index + 1]);
		ft_pipe_close(&vars);
		vars.cmd_args = ft_split(argv[2 + vars.here_doc + vars.index], ' ');
		vars.cmd = ft_cmd_const(vars.cmd_paths, vars.cmd_args[0]);
		if (!vars.cmd)
		{
			printf("Command not found: %s\n", vars.cmd_args[0]);
			ft_free_childs(&vars);
			exit(-1);
		}
		execve(vars.cmd, vars.cmd_args, envp);
	}
}
