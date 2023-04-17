/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:48:42 by bcaffere          #+#    #+#             */
/*   Updated: 2023/04/13 19:16:05 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//	write, read, close, access, pipe, dup, dup2, execve, fork
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

//	malloc, free, exit
# include <stdlib.h>

//	open, unlink 
# include <fcntl.h>

//	waitpid, wait
# include <sys/wait.h>

//	strerror
# include <string.h>

//	to perror
# include <stdio.h>

//	get_next_line
# include "./42_gnl/gnl.h"

//	ft_printf
# include "./42_ft_printf/includes/ft_printf.h"

//	ft_libft
# include "./42_libft/libft.h"

# define ERR_INFILE "Infile Error"
# define ERR_OUTFILE "Outfile Error"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe Error"
# define ERR_CMD "Command not found\n"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	*cmd;
	char	**cmd_paths;
	char	**cmd_args;
}t_pipex;

//	childs.c
void	ft_first_child(t_pipex pipex, char *argv[], char *envp[]);
void	ft_second_child(t_pipex pipex, char *argv[], char *envp[]);

//	free.c 
void	ft_parent_free(t_pipex *pipex);
void	ft_child_free(t_pipex *pipex);

//	error.c
void	ft_error(char *err);
int		ft_msg(char *err);

//	pipex.c
char	*ft_find_path(char **envp);
void	ft_close_pipes(t_pipex *pipex);
int		main(int argc, char *argv[], char *envp[]);

#endif
