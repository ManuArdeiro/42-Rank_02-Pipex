/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:43:45 by bcaffere          #+#    #+#             */
/*   Updated: 2023/04/22 12:58:47 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*	Function to print an error message and return 1. */

int	ft_message(int msg_nb, char *msg_text)
{
	perror(msg_text);
	return (msg_nb);
}

/*	Function to print an error message and exit (with 1). */

void	ft_error(int error_nb, char *error_text)
{
	perror(error_text);
	exit (error_nb);
}

/*	This function frees allocated memory (cmd_paths in struct vars)
	and closes the open files*/

void	ft_parent_free(t_vars *vars)
{
	close(vars->infile);
	close(vars->outfile);
/*	while (vars->cmd_paths[i])
	{
		free(vars->cmd_paths[i]);
		i++;
	}*/
	free(vars->cmd_paths);
}
