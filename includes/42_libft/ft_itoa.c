/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:28:33 by jolopez-          #+#    #+#             */
/*   Updated: 2022/04/10 14:57:33 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdio.h>

static int	ft_len_nbr(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = n / 10;
		i++;
		n = n * -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		nbr = -nbr;
	return (nbr);
}

static void	ft_strrev(char *str)
{
	size_t	length;
	size_t	i;
	char	tmp;

	length = ft_strlen(str);
	i = 0;
	while (i < length / 2)
	{
		tmp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = tmp;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		is_neg;
	size_t	length;

	is_neg = (n < 0);
	length = ft_len_nbr(n);
	str = ft_calloc(length + 1, sizeof(*str));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length] = '0' + ft_abs(n % 10);
		n = (n / 10);
		length++;
	}
	if (is_neg)
		str[length] = '-';
	ft_strrev(str);
	return (str);
}

/*int	main(void)
{
	long long		n = -2147483648LL;
	char	*i;

	i = ft_itoa(n);
	printf("n = %d\nft_itoa = %s\n", (int)n, i);
	return (0);
}*/
