/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:48:42 by bcaffere          #+#    #+#             */
/*   Updated: 2023/07/08 13:15:49 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//	write, read, close, access, pipe, dup, dup2, execve, fork, errno
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <errno.h>

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
# include "./42_gnl/get_next_line.h"

//	ft_printf
# include "./42_ft_printf/includes/ft_printf.h"

//	ft_libft
# include "./42_libft/libft.h"

typedef struct s_vars
{
	pid_t	pid_one;
	pid_t	pid_two;
	int		infile;
	int		outfile;
	int		tube[2];
	char	*paths;
	char	*cmd;
	char	**cmd_paths;
	char	**cmd_args;
}t_vars;

//		childs.c
char	*ft_cmd_const(char **paths, char *cmd);
int		ft_count_parts(char *str, char c);
void	ft_first_child(t_vars *vars, char *argv[], char *envp[]);
void	ft_second_child(t_vars *vars, int argc, char *argv[], char *envp[]);

//		pipex.c
char	*ft_path_search(char **envp);
void	ft_close_pipes(t_vars *vars);
void	ft_close_files(t_vars *vars);
int		ft_waitpids(t_vars *vars);
int		main(int argc, char *argv[], char *envp[]);

//		tools.c
int		ft_error_message(char *str_1, char *str_2, char *str_3, int nb);
void	ft_error(int error_nb, char *error_text);
void	ft_parent_free(t_vars *vars);
int		ft_init_vars(int argc, char **argv, char **envp, t_vars *vars);

#endif
