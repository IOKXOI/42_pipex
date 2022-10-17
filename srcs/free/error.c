/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:55:45 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/15 19:39:53 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str, t_elements *elements)
{
	if (elements->paths)
		free_paths(elements->paths);
	if (elements->first)
		free_list(elements->first);
	if (elements->here_doc)
		free(elements->here_doc);
	perror(str);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}
