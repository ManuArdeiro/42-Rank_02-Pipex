/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:33:11 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/08 12:22:58 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	ft_here_doc_arg(char *arg_one, t_vars *vars)
{
	if (arg_one && !ft_strncmp("here_doc", arg_one, 9))
	{
		vars->here_doc = 1;
		return (6);
	}
	else
	{
		vars->here_doc = 0;
		return (5);
	}
}

void	ft_here_doc(char *infile, t_vars *vars)
{
	int		file;
	char	*line;

	line = 0;
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (file < 0)
		ft_error("here_doc error.\n", vars->infile);
	while (1)
	{
		write(1, "heredoc> ", 9);
		if (ft_gnl(0, line) < 0)
			exit(-1);
		if (!ft_strncmp(infile, line, ft_strlen(infile) + 1))
			break ;
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		free(line);
	}
	free(line);
	close(file);
	vars->infile = open(".heredoc_tmp", O_RDONLY);
	if (vars->infile < 0)
	{
		unlink(".heredoc_tmp");
		ft_error("here_doc error.\n", vars->infile);
	}
}
