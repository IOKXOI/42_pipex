/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:05:18 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/17 21:33:34 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parent(int pid, char *commands, t_elements *elements)
{
	int	status;

	elements->pipefd[2] = elements->pipefd[0];
	close(elements->pipefd[1]);
	free(commands);
	waitpid(pid, &status, 0);
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
