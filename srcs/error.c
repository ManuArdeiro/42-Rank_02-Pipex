/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:43:45 by bcaffere          #+#    #+#             */
/*   Updated: 2023/04/13 17:30:35 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (0);
}

void	ft_error(char *err)
{
	perror(err);
	exit (-1);
}
