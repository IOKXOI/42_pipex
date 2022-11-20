/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:53:30 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/13 00:45:37 by iok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	*init_pid_register(int argc, t_elements *elements)
{
	int *pid_register;
	int	nb_commands;

	nb_commands = argc - 3;

	pid_register = malloc(sizeof(int) * nb_commands);
	if (!pid_register)
		error("Malloc: impossible to create pid_register", elements);
	return (pid_register);
}

static char	**parse_paths(char *envp[], t_elements *elements)
{
	int		i;
	char	**paths;
	char	*tmp;

	i = 0;
	while (envp[i] && ((envp[i][0] != 'P') || (envp[i][1] != 'A')
		|| (envp[i][2] != 'T') || (envp[i][3] != 'H') || (envp[i][4] != '=')))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		error("parse_paths : ft_split", elements);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		if (!paths[i])
		{
			
		}
		if (!paths[i])
			error("parse_paths : ft_strjoin", elements);
		free(tmp);
		i++;
	}
	return (paths);
}

static char	**parse_files(char *argv[], t_elements *elements)
{
	char	**files;

	files = malloc(sizeof(char *) * 2);
	if (!files)
		error("parse_files : malloc", elements);
	files[0] = ft_strdup(argv[1]);
	if (!files[0])
		error("parse_files : ft_strdup", elements);
	files[1] = ft_strdup(argv[elements->argc - 1]);
	if (!files[1])
		error("parse_files : ft_strdup", elements);
	return (files);
}

static t_commands	*parse_commands(char *argv[], t_elements *elements)
{
	int		i;

	i = 2;
	if (!ft_strcmp(argv[1], "here_doc"))
		i++;
	new_node(elements);
	elements->first->commands = ft_split(argv[i], ' ');
	if (!elements->first->commands)
		error("parse_commands : malloc tab on the node", elements);
	i++;
	while (i < (elements->argc - 1))
	{
		new_node(elements);
		elements->last->commands = ft_split(argv[i], ' ');
		if (!elements->last->commands)
			error("parse_commands : malloc tab on the node", elements);
		i++;
	}
	return (elements->first);
}

void	init_struct(int argc, char *argv[], char *envp[], t_elements *elements)
{
	elements->argc = argc;
	elements->here_doc = NULL;
	elements->paths = NULL;
	elements->first = NULL;
	elements->pid_register = NULL;
	check_argv(argc, argv);
	elements->node_commands = parse_commands(argv, elements);
	elements->paths = parse_paths(envp, elements);
	elements->files = parse_files(argv, elements);
	elements->pid_register = init_pid_register(argc, elements);
}