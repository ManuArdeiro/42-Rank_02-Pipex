# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 20:30:47 by jolopez-          #+#    #+#              #
#    Updated: 2023/07/14 21:03:07 by jolopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	pipex

BONUS_NAME	=	pipex

SRCS 		= 	srcs/childs.c \
				srcs/pipex.c \
				srcs/tools.c

SRCS_BONUS	=	srcs/bonus/child_bonus.c \
				srcs/bonus/files_bonus.c \
				srcs/bonus/here_doc_bonus.c \
				srcs/bonus/pipex_bonus.c \
				srcs/bonus/tools_bonus.c

OBJS		= $(SRCS:%.c=%.o)

BONUS_OBJS	= $(SRCS_BONUS:%.c=%.o)

INC 		= -I./includes/

LIBS		= ./includes/42_libft/libft.a ./includes/42_ft_printf/libftprintf.a ./includes/42_gnl/libgnl.a

CC = 		gcc

CFLAGS = 	-Wall -Werror -Wextra -I $(INC) -fsanitize=address -g3

all: $(NAME)

$(NAME):	$(OBJS)
			@echo "$(LIGHT_RED) Creating libft files... $(WHITE)"
			cd ./includes/42_libft && make
			@echo "$(LIGHT_RED) Creating ft_printf files... $(WHITE)"
			cd ./includes/42_ft_printf && make bonus
			@echo "$(LIGHT_RED) Creating gnl files... $(WHITE)"
			cd ./includes/42_gnl && make
			@echo "$(YELLOW) Creating pipex... $(WHITE)"
			${CC} $(CFLAGS) -o ${NAME} $(OBJS) ${LIBS}
			@echo "$(GREEN) Done..."			
			
bonus:		$(BONUS_OBJS)
			@echo "$(LIGHT_RED) Creating libft files... $(WHITE)"
			make -C includes/42_libft
			@echo "$(LIGHT_RED) Creating ft_printf files... $(WHITE)"
			make -C includes/42_ft_printf
			@echo "$(LIGHT_RED) Creating gnl files... $(WHITE)"
			cd ./includes/42_gnl && make
			@echo "$(YELLOW) Creating pipex with bonus... $(WHITE)"
			${CC} $(CFLAGS) -o ${BONUS_NAME} ${BONUS_OBJS} ${LIBS}
			@echo "$(GREEN) Done..."			

clean:		
			@echo "$(LIGHT_RED) Cleaning libft objects... $(WHITE)"
			make clean -C includes/42_libft
			@echo "$(LIGHT_RED) Cleaning ft_printf objects... $(WHITE)"
			make clean -C includes/42_ft_printf
			@echo "$(LIGHT_RED) Cleaning gnl objects.. $(WHITE)"
			make clean -C includes/42_gnl
			@echo "$(LIGHT_RED) Cleaning pipex objects.. $(WHITE)"
			/bin/rm -rf $(OBJS) $(BONUS_OBJS)
			@echo "$(LIGHT_RED) Done!! $(WHITE)"

fclean: 	
			@echo "$(LIGHT_RED) Cleaning all from libft... $(WHITE)"
			cd ./includes/42_libft && make fclean 
			@echo "$(LIGHT_RED) Cleaning all from ft_printf... $(WHITE)"
			cd ./includes/42_ft_printf && make fclean
			@echo "$(LIGHT_RED) Cleaning all from gnl... $(WHITE)"
			cd ./includes/42_gnl && make fclean 
			@echo "$(LIGHT_RED) Cleaning all from pipex... $(WHITE)"
			/bin/rm -rf $(NAME) $(BONUS_NAME) $(OBJS) $(BONUS_OBJS)
			@echo "$(LIGHT_RED) Done!! $(WHITE)"

re: 		fclean all

.PHONY: 	all clean fclean re bonus

# COLORS
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENTA		= \033[0;35m
CYAN		= \033[0;36m
LIGHT_GRAY	= \033[0;37m
DARK_GRAY	= \033[0;90m
LIGHT_RED	= \033[0;91m
WHITE		= \033[0;97m

#SETS
BOLD		= \e[0;1m
UNDERLINED	= \e[0;4m
BLINK		= \e[0;5m
