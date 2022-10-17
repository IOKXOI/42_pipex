/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 05:05:57 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/17 21:20:20 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*try_to_access(char **commands, t_elements *elements)
{
	int		i;
	char	*paths;

	i = 0;
	if (!access(commands[0], X_OK))
		return (commands[0]);
	else if (elements->paths)
	{
		paths = ft_strjoin(elements->paths[i], commands[0]);
		while (access(paths, X_OK))
		{
			i++;
			free(paths);
			if (!elements->paths[i])
			{
				if (!access(commands[0], X_OK))
					return (commands[0]);
				else
					return (perror(commands[0]), NULL);
			}
			paths = ft_strjoin(elements->paths[i], commands[0]);
		}
	}
	return (paths);
}

void	check_argv(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!*argv[i])
		{
			access(argv[i], F_OK);
			if (i == 1 || i == argc - 1)
				perror("Parse error:");
			else
				perror("Parse error:");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
