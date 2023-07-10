/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 13:19:27 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/10 19:22:59 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*ft_gnl(int fd, char *line);
char	*ft_read_buffer(int fd, char *str);
char	*ft_get_line(char *container);
char	*ft_new_container(char *container);
size_t	ft_str_len(char *s);
char	*ft_str_find_chr(char *s, int c);
char	*ft_str_join_buffer(char *container, char *buffer);

#endif
