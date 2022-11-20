/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:25:28 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/20 20:49:15 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_cmd(char *commands, int *pipefd, t_elements *elements)
{
	int	fd;

	fd = open(elements->files[0], O_RDONLY);
	if (fd < 0)
	{
		free(commands);
		error(elements->files[0], elements);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		free(commands);
		error("first_cmd: dup2", elements);
	}
	close(fd);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
	{
		free(commands);
		error("first_cmd: dup2", elements);
	}
	close(pipefd[1]);
	close(pipefd[0]);
}

static void	last_cmd(char *commands, int *pipefd, t_elements *elements)
{
	int	new_fd;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		free(commands);
		error("last_cmd: dup2", elements);
	}
	new_fd = open(elements->files[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_fd == -1)
	{
		free(commands);
		error("last_cmd: open", elements);
	}
	if (dup2(new_fd, STDOUT_FILENO) < 0)
	{
		free(commands);
		error("last_cmd: dup2", elements);
	}
	close(pipefd[0]);
	close(new_fd);
}

void	child_process(t_commands *node, char **envp, t_elements *e)
{
	char		*commands;

	commands = try_to_access(node->commands, e);
	if (node == e->first)
		first_cmd(commands, e->pipefd, e);
	else
		last_cmd(commands, e->pipefd, e);
	if (commands)
	{
		close(e->pipefd[0]);
		close(e->pipefd[1]);
		if (execve(commands, node->commands, envp) == -1)
		{
			free(commands);
			error("exec error", e);
		}
	}
	close(e->pipefd[0]);
	close(e->pipefd[1]);
	error_127(e);
}

void	pipe_creator(t_elements *elements)
{
	if (pipe(elements->pipefd) < 0)
		error("on forking : pipe", elements);
}

int	forking(t_elements *elements, char *envp[])
{
	int			i;
	int			ret;
	t_commands	*node;

	i = 0;
	node = elements->first;
	pipe_creator(elements);
	while (node)
	{
		elements->pid_register[i] = fork();
		if (elements->pid_register[i] < 0)
			error("Forking", elements);
		else if (elements->pid_register[i] == 0)
			child_process(node, envp, elements);
		else
		{
			close(elements->pipefd[1]);
			node = node->next;
			i++;
		}
	}
	close(elements->pipefd[0]);
	close(elements->pipefd[1]);
	ret = wait_id(elements);
	return (ret);
}
