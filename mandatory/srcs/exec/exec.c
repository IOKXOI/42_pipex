/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:25:28 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/20 16:24:18 by iok              ###   ########.fr       */
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
		error(elements->files[0], elements);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		error("first_cmd: dup2", elements);
	close(fd);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		error("first_cmd: dup2", elements);
	close(pipefd[0]);
	close(pipefd[1]);
}

static void	last_cmd(int *pipefd, t_elements *elements)
{
	int	new_fd;
	
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		error("last_cmd: dup2", elements);
	new_fd = open(elements->files[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_fd == -1)
	{
		free_files(elements->files);
		error("last_cmd: open", elements);
	}
	if (dup2(new_fd, STDOUT_FILENO) < 0)
		error("last_cmd: dup2", elements);
	close(pipefd[0]);
	close(new_fd);
}

void	child_process(t_commands *node, char **envp, t_elements *e)
{
	char		*commands;
	//t_commands	*tmp;
	
	commands = try_to_access(node->commands, e);
	if (commands == NULL)
	{
		//tmp = node;
		//node = node->next;
		close(e->pipefd[0]);
		close(e->pipefd[1]);
		//free_this_node(tmp, e);
	//	exit(EXIT_FAILURE);
	}
	else 
	{
		if (node == e->first)
			first_cmd(e->pipefd, e);
		else
			last_cmd(e->pipefd, e);
		if (execve(commands, node->commands, envp) == -1)
			error("exec error", e);
	}
	free_files(e->files);
	error_127("ICI", e);
}


void	pipe_creator(t_elements *elements)
{
	if (pipe(elements->pipefd) < 0)
		error("on forking : pipe", elements);
	
	//verif ecole 
	
	//if (!*node->commands)
	//	error("Parse error : missing commande", elements);
//	if (!*node->commands)
//		error("command not found");
}

int	wait_id(t_elements *elements)
{
	int	i;
	int	status;

	i = 0;

	while(i < (elements->argc - 3))
	{
		waitpid(elements->pid_register[i], &status, 0);
		i++;
	}
	if (WIFSIGNALED(status))
		return(128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	return (0);
}

int	forking(t_elements *elements, char *envp[])
{
	int			i;
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
	int ret = wait_id(elements);
	free(elements->pid_register);
	return (ret);
}

