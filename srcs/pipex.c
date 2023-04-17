/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:58:39 by jolopez-          #+#    #+#             */
/*   Updated: 2023/04/13 19:25:40 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_find_path(char **envp)
{
	int	i;
	
	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		i++;
	return (envp[i] + 5);
}

void	ft_close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		return (msg(ERR_INPUT));
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_error(ERR_INFILE);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 00644);
	if (pipex.outfile < 0)
		ft_error(ERR_OUTFILE);
	if (pipe(pipex.tube) < 0)
		ft_error(ERR_PIPE);
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		ft_first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		ft_second_child(pipex, argv, envp);
	ft_close_pipes(&pipex);
	waitpid(pipex.pid1, 0, 0);
	waitpid(pipex.pid2, 0, 0);
	ft_parent_free(&pipex);
	return (0);
}
