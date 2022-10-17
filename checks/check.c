/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 05:05:57 by sydauria          #+#    #+#             */
/*   Updated: 2022/09/22 06:43:37 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_command(char *argv[], int *fd)
{
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	fd[1] = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 644);
	if (fd[1] == -1)
		perror(argv[4]);
	if (fd[0] == -1 || fd[1] == -1)
		exit(EXIT_FAILURE);
}
