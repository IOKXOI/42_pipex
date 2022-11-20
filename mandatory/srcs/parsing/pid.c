/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:38:20 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/20 20:48:48 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	*init_pid_register(int argc, t_elements *elements)
{
	int	*pid_register;
	int	nb_commands;

	nb_commands = argc - 3;
	pid_register = malloc(sizeof(int) * nb_commands);
	if (!pid_register)
		error("Malloc: impossible to create pid_register", elements);
	return (pid_register);
}

int	wait_id(t_elements *elements)
{
	int	i;
	int	status;

	i = 0;
	while (i < (elements->argc - 3))
	{
		waitpid(elements->pid_register[i], &status, 0);
		i++;
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
