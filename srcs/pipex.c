/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:31:23 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/24 03:02:50 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int			ret;
	t_elements	elements;

	if (argc != 5 || !envp || !*envp)
		return (1);
	init_struct(argc, argv, envp, &elements);
	ret = forking(&elements, envp);
	free(elements.pid_register);
	free_paths(elements.paths);
	free_files(elements.files);
	free_list(elements.first);
	return (ret);
}
