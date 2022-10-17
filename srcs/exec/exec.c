/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:25:28 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/17 21:32:41 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_cmd(int *pipefd, t_elements *elements)
{
	int	fd;

	fd = open(elements->files[0], O_RDONLY);
	if (fd < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		error("First_cmd : Cannot open files", elements);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		error("first_cmd : dup2", elements);
	close(fd);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		error("first_cmd : dup2", elements);
}

static void	intermediate_cmd(int *pipefd, t_elements *elements)
{
	if (dup2(pipefd[2], STDIN_FILENO) < 0)
		error("intermediate_cmd : dup2", elements);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		error("intermediate_cmd : dup2", elements);
}

static void	last_cmd(int *pipefd, t_elements *elements)
{
	if (dup2(pipefd[2], STDIN_FILENO) < 0)
		error("last_cmd : dup2", elements);
	if (dup2(open(elements->files[1], \
	O_WRONLY | O_CREAT | O_TRUNC, 0644), STDOUT_FILENO) < 0)
		error("last_cmd : dup2", elements);
	close(pipefd[1]);
}

void	ft_child(char *commands, t_commands *node, char **envp, t_elements *e)
{
	if (node == e->first)
		first_cmd(e->pipefd, e);
	else if (node != e->last)
		intermediate_cmd(e->pipefd, e);
	else
		last_cmd(e->pipefd, e);
	(void)commands;
	(void)envp;
	execve(commands, node->commands, envp);
	exit(EXIT_SUCCESS);
}

void	forking(t_elements *elements, char *envp[])
{
	char		*commands;
	t_commands	*node;
	t_commands	*tmp;

	node = elements->first;
	while (node)
	{
		if (pipe(elements->pipefd) < 0)
			error("on forking : pipe", elements);
		if (!*node->commands)
			error("Parse error : missing commande", elements);
		commands = try_to_access(node->commands, elements);
		if (commands == NULL)
		{
			tmp = node;
			node = node->next;
			free_this_node(tmp, elements);
		}
		else
		{
			process(commands, node, envp, elements);
			node = node->next;
		}
	}
	close(elements->pipefd[0]);
}
