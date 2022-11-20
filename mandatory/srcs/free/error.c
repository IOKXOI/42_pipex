/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:55:45 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/20 14:02:12 by iok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str, t_elements *elements)
{
	if (elements->paths)
		free_paths(elements->paths);
	if (elements->first)
		free_list(elements->first);
	//if (elements->files)
	//	free_files(elements->files);
	if (elements->here_doc)
		free(elements->here_doc);
	if (elements->pid_register)
		free(elements->pid_register);
	perror(str);
	/// 
	//write(1, "\n", 1);
	///
	exit(EXIT_FAILURE);
}

void	error_127(char *str, t_elements *elements)
{
	if (elements->paths)
		free_paths(elements->paths);
	if (elements->first)
		free_list(elements->first);
	if (elements->here_doc)
		free(elements->here_doc);
	if (elements->pid_register)
		free(elements->pid_register);
	perror(str);
	/// 
	//write(1, "\n", 1);
	///
	exit(127);
}