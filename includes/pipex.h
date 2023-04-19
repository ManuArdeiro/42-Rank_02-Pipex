/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:48:42 by bcaffere          #+#    #+#             */
/*   Updated: 2023/04/19 01:55:03 by jolopez-         ###   ########.fr       */
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

typedef struct s_vars
{
	pid_t	pid1;
	pid_t	pid2;
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
void	ft_first_child(t_vars vars, char *argv[], char *envp[]);
void	ft_second_child(t_vars vars, char *argv[], char *envp[]);

//		pipex.c
char	*ft_path_search(char **envp);
void	ft_close_pipes(t_vars *vars);
int		main(int argc, char *argv[], char *envp[]);

//		tools.c
int		ft_message(char *message);
void	ft_error(char *error);
void	ft_parent_free(t_vars *vars);

#endif
