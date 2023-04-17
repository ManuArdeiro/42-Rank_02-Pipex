/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:33:08 by jolopez-          #+#    #+#             */
/*   Updated: 2022/04/03 19:08:53 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		nbr = -nbr;
	return (nbr);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	int		is_neg;
	int		length;

	is_neg = (n < 0);
	ft_bzero(str, 12);
	length = 0;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	while (n != 0)
	{
		str[length] = '0' + ft_abs(n % 10);
		n = (n / 10);
		length++;
	}
	if (is_neg)
		str[length] = '-';
	else if (length > 0)
		length--;
	while (length >= 0)
		write(fd, &str[length--], 1);
}
