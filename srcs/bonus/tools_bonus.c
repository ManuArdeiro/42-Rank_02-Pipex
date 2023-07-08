/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:32:40 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/08 12:24:29 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

/*	Function to print an error message and return 1. */

int	ft_message(int msg_nb, char *msg_text)
{
	write(STDERR_FILENO, msg_text, ft_strlen(msg_text));
	return (msg_nb);
}

/*	Function to print an error message and exit (with 1). */

void	ft_error(int error_nb, char *error_text)
{
	perror(error_text);
	exit (error_nb);
}

void	ft_free_parents(t_vars *vars)
{
	int	i;

	i = 0;
	close(vars->infile);
	close(vars->outfile);
	if (vars->here_doc)
		unlink(".heredoc_tmp");
	while (vars->cmd_paths[i])
	{
		free(vars->cmd_paths[i]);
		i++;
	}
	free(vars->cmd_paths);
	free(vars->pipe);
}

void	ft_free_childs(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->cmd_args[i])
	{
		free(vars->cmd_args[i]);
		i++;
	}
	free(vars->cmd_args);
	free(vars->cmd);
}

void	ft_free_mem(t_vars *vars)
{
	close(vars->infile);
	close(vars->outfile);
	if (vars->here_doc)
		unlink(".heredoc_tmp");
	free(vars->pipe);
	ft_message("envp error.\n");
	exit(-1);
}
