/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:05:18 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/13 01:38:06 by iok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void	parent_process(int pid, char *commands, t_elements *elements)
{
	size_t	index;
	
	index = search_index_pid(pid);
	elements->pid_register[index] = pid;
	elements->pipefd[2] = elements->pipefd[0];
	close(elements->pipefd[1]);
	free(commands);
}

void	process(char *commands, t_commands *node, char *envp[], t_elements *e)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		ft_child(commands, node, envp, e);
	else
		ft_parent(pid, commands, e);
}
*/
/*
void waitid(int *pid, int i)
{
	int	status;
	
	while (i)
	{
		waitpid(pid[i], &status, 0);
		i--;
	}
	free(pid);
}
*/