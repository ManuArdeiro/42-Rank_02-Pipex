/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:32:40 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/14 20:53:27 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

/*	Function to print an error text message and return nb provided. */

int	ft_message(int msg_nb, char *msg_text)
{
	write(STDERR_FILENO, msg_text, ft_strlen(msg_text));
	return (msg_nb);
}

/*	Function to print an error message and exit (with nb provided). */

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
	ft_message(7, "envp error.\n");
	exit(-1);
}
