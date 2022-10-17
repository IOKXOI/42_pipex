/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:25:28 by sydauria          #+#    #+#             */
/*   Updated: 2022/09/22 08:52:39 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	exec(char *commands[], char *argv[], char *paths[])
{
	int	i = 0;

	while ((argc - 3) - i)
	{
		search_path(commands[i], paths);
		fork()
	}
}
