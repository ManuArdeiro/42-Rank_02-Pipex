/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:58:39 by jolopez-          #+#    #+#             */
/*   Updated: 2023/04/24 19:35:47 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*	function to find paths in enviroment	*/

char	*ft_path_search(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		while (ft_strncmp("PATH=", envp[i], 5))
			i++;
		return (envp[i] + 5);
	}
	return (0);
}

/*	Function to close pipes	*/

void	ft_close_pipes(t_vars *vars)
{
	close(vars->tube[0]);
	close(vars->tube[1]);
}

/*	Main function:
	1.- It checks arguments.
	2.- It checks if enviroment is provided in arguments and manage it if so.
	3.- It gets the command paths.
	4.- It makes a fork;
		a)	The child will manage the firs command.
		b)	The parent makes another fork.
			-	The (second) child manage ethe second command.
			-	The (second) parent will free memory and finish the program	*/

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	if (argc != 5)
		return (ft_message(EXIT_FAILURE, "Invalid number of arguments.\n"));
	if (pipe(vars.tube) < 0)
		ft_error(EXIT_FAILURE, "pipe");
	vars.paths = ft_path_search(envp);
	vars.cmd_paths = ft_split(vars.paths, ':');
	vars.pid_one = fork();
	if (vars.pid_one == 0)
		ft_first_child(vars, argv, envp);
	vars.pid_two = fork();
	if (vars.pid_two == 0)
		ft_second_child(vars, argc, argv, envp);
	ft_close_pipes(&vars);
	if (waitpid(vars.pid_one, 0, 0) < 0)
		return (1);
	if (waitpid(vars.pid_two, 0, 0) < 0)
		return (1);
	ft_parent_free(&vars);
}
