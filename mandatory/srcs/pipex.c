/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:31:23 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/20 16:21:39 by iok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_elements	elements;

	if (argc != 5 || !envp || !*envp)
		return (1);
	init_struct(argc, argv, envp, &elements);
	int ret = forking(&elements, envp);
	free_paths(elements.paths);
	free_files(elements.files);
	free_list(elements.first);
	return (ret);
}