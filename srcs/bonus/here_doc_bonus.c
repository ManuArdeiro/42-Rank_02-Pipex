/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:33:11 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/10 20:17:25 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

/*	Function to determine if first argument is here_doc	*/

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

/*	Function to read here_doc input	*/

void	ft_here_doc(char *limiter, t_vars *vars)
{
	int		file;
	char	*line;

	line = malloc(sizeof(char *) * 1);
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (file < 0)
		ft_error(3, "here_doc error.\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = ft_gnl(0, line);
		if (line <= 0)
			exit(-1);
		if (ft_strncmp(limiter, line, ft_strlen(limiter) + 1) == 0)
			break ;
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		free(line);
	}
	close(file);
	vars->infile = open(".heredoc_tmp", O_RDONLY);
	if (vars->infile < 0)
	{
		unlink(".heredoc_tmp");
		ft_error(3, "here_doc error.\n");
	}
}
