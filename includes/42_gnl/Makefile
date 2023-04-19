# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 18:18:30 by jolopez-          #+#    #+#              #
#    Updated: 2023/04/19 18:19:52 by jolopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	get_next_line_utils.c \
					get_next_line.c
					

OBJS			=	$(SRCS:.c=.o)

CC				=	gcc

RM				=	rm -f

CFLAGS			=	-Wall -Wextra -Werror -g3

NAME			=	libgnl.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re