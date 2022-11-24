/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 05:05:57 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/24 04:21:06 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*commands_errors(char **commands)
{
	if (access(commands[0], F_OK))
		ft_printf("%s: command not found\n", commands[0]);
	else if (access(commands[0], X_OK))
		ft_printf("%s: permission denied\n", commands[0]);
	return (NULL);
}	

char	*get_good_paths(char **commands, t_elements *elements)
{
	int		i;
	char	*paths;

	i = 0;
	paths = ft_strjoin(elements->paths[i], commands[0]);
	if (!paths)
		perror("try_to_access: ft_strjoin");
	while (access(paths, F_OK))
	{
		i++;
		free(paths);
		if (!elements->paths[i])
		{
			if (!access(commands[0], F_OK | X_OK))
				return (commands[0]);
			else
				return (commands_errors(commands));
		}
		paths = ft_strjoin(elements->paths[i], commands[0]);
		if (!paths)
			perror("try_to_access: ft_strjoin");
	}
	return (paths);
}

char	*try_to_access(char **commands, t_elements *elements)
{
	char	*paths;

	if (!commands[0])
		error_127(elements);
	if (!access(commands[0], F_OK | X_OK))
		return (ft_strdup(commands[0]));
	else if (elements->paths)
		paths = get_good_paths(commands, elements);
	return (paths);
}
/*
void	check_argv(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (*argv[i])
		{
			access(argv[i], F_OK);
			if (i == 1 || i == argc - 1)
			{
				if (i == 1)
					ft_printf("%s: ");
			}
		}
		i++;
	}
}
*/
