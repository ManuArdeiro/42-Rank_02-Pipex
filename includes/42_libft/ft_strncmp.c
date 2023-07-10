/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:32:52 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/10 20:40:30 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdio.h>
#include<string.h>

int	cmp_char(char c1, char c2)
{
	if ((unsigned char)c1 != (unsigned char)c2)
		return ((unsigned char)c1 - (unsigned char)c2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (cmp_char(s1[i], s2[i]))
			return (cmp_char(s1[i], s2[i]));
		i++;
	}
	if (i < n)
		return (cmp_char(s1[i - 1], s2[i - 1]));
	return (0);
}
