/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:58:40 by bcaffere          #+#    #+#             */
/*   Updated: 2023/04/13 21:24:43 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*ft_get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (0);
}

void	ft_first_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		ft_child_free(&pipex);
		ft_msg(ERR_CMD);
		exit(-1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	ft_second_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		ft_child_free(&pipex);
		ft_msg(ERR_CMD);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
