/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 13:21:51 by jolopez-          #+#    #+#             */
/*   Updated: 2023/04/19 18:23:57 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_str_len(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_str_find_chr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_str_len(s)]);
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_str_join_buffer(char *container, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*sol;

	if (!container)
	{
		container = malloc(sizeof(char) * 1);
		container[0] = '\0';
	}
	if (!buffer || !container)
		return (0);
	sol = malloc(sizeof(char) * ft_str_len(container) + ft_str_len(buffer) + 1);
	if (sol == 0)
		return (0);
	i = -1;
	j = -1;
	if (container)
		while (container[++i] != '\0')
			sol[i] = container[i];
	while (buffer[++j] != '\0')
		sol[i++] = buffer[j];
	sol[ft_str_len(container) + ft_str_len(buffer)] = '\0';
	free (container);
	return (sol);
}
