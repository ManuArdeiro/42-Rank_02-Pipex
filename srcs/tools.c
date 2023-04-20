/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:43:45 by bcaffere          #+#    #+#             */
/*   Updated: 2023/04/20 17:17:44 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*	Function to print an error message and return 1. */

int	ft_message(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	return (1);
}

/*	Function to print an error message and exit (with 1). */

void	ft_error(char *error)
{
	perror(error);
	exit (1);
}

/*	This function frees allocated memory (cmd_paths in struct vars)
	and closes the open files*/

void	ft_parent_free(t_vars *vars)
{
	int	i;

	i = 0;
	close(vars->infile);
	close(vars->outfile);
	while (vars->cmd_paths[i])
	{
		free(vars->cmd_paths[i]);
		i++;
	}
	free(vars->cmd_paths);
}
