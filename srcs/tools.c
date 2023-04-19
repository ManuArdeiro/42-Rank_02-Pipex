/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:43:45 by bcaffere          #+#    #+#             */
/*   Updated: 2023/04/18 20:08:19 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_message(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	return (-1);
}

void	ft_error(char *error)
{
	perror(error);
	exit (-1);
}

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
