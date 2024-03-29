/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:30:46 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/13 18:52:50 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <errno.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/*to perror*/
# include <stdio.h>

/* to get_next_line */
# include "./42_gnl/get_next_line.h"

//	ft_printf
# include "./42_ft_printf/includes/ft_printf.h"

//	ft_libft
# include "./42_libft/libft.h"

typedef struct s_vars
{
	pid_t	pid;
	int		infile;
	int		outfile;
	int		here_doc;
	int		commands_nb;
	int		pipes_nb;
	int		index;
	int		*pipe;
	char	*paths;
	char	*cmd;
	char	**cmd_args;
	char	**cmd_paths;
}t_vars;

//		child_bonus.c
char	*ft_cmd_const(char **paths, char *cmd);
int		ft_count_parts(char *str, char c);
void	ft_double_dup(int in, int out);
void	ft_childs(t_vars *vars, char **argv, char **envp);

//		files_bonus.c
char	*ft_path_search(char **envp);
void	ft_infile(char **argv, t_vars *vars);
void	ft_outfile(char *outfile, t_vars *vars);

//		pipex_bonus.c
void	ft_pipe_creation(t_vars *vars);
void	ft_pipe_close(t_vars *vars);
int		main(int argc, char *argv[], char *envp[]);

//		here_doc_bonus.c
int		ft_here_doc_arg(char *arg_one, t_vars *vars);
void	ft_here_doc_write(char *limiter, t_vars *vars);
void	ft_here_doc_read(t_vars *vars);

//		tools_bonus.c
int		ft_message(int msg_nb, char *msg_text);
void	ft_error(int error_nb, char *error_text);
void	ft_free_parents(t_vars *vars);
void	ft_free_childs(t_vars *vars);
void	ft_free_mem(t_vars *vars);

#endif
