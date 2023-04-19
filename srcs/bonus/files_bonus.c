/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:32:50 by jolopez-          #+#    #+#             */
/*   Updated: 2023/04/19 01:04:17 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

char	*ft_path_search(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	ft_infile(char **argv, t_vars *vars)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		ft_here_doc(argv[2], vars);
	else
	{
		vars->infile = open(argv[1], O_RDONLY);
		if (vars->infile < 0)
			ft_error("Infile error.\n");
	}
}

void	ft_outfile(char *outfile, t_vars *vars)
{
	if (vars->here_doc)
		vars->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 00644);
	else
		vars->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (vars->outfile < 0)
		ft_error("Outfile error.\n");
}
