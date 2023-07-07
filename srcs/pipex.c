/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:58:39 by jolopez-          #+#    #+#             */
/*   Updated: 2023/07/07 20:17:37 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*	Function to find paths in enviroment.	*/

char	*ft_path_search(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
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
	int		exit_code;
	int		status;
	t_vars	*vars;

	exit_code = 0;
	vars = malloc(sizeof(t_vars) * 1);
	if (argc != 5)
		return (ft_error_message("Invalid number of arguments.", "", "", 1));
	exit_code = ft_init_vars(argc, argv, envp, vars);
	if (exit_code != 0)
	{
		close(vars->infile);
		close(vars->outfile);
		return (exit_code);
	}
	vars->pid_one = fork();
	if (vars->pid_one < 0)
		return (ft_error_message("Fork", ": ", strerror(errno), errno));
	else if (vars->pid_one == 0)
		ft_first_child(vars, argv, envp);
	vars->pid_two = fork();
	if (vars->pid_two == -1)
		return (ft_error_message("Fork", ": ", strerror(errno), errno));
	else if (vars->pid_two == 0)
		ft_second_child(vars, argc, argv, envp);
	ft_close_pipes(vars);
	close(vars->infile);
	close(vars->outfile);
	waitpid(vars->pid_one, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	waitpid(vars->pid_two, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	ft_parent_free(vars);
	exit_code = 2;
	return (exit_code);
}
