/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:31:23 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/17 21:00:57 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int			here_docfd;
	t_elements	elements;

	if (argc < 5 || !envp || !*envp)
		return (1);
	init_struct(argc, argv, envp, &elements);
	if (!ft_strcmp(elements.files[0], "here_doc"))
		here_doc(argv[2], &elements);
	forking(&elements, envp);
	if (elements.here_doc)
	{
		here_docfd = open(elements.here_doc, O_RDONLY);
		if (here_docfd < 0)
			error("", &elements);
		unlink(elements.here_doc);
		close(here_docfd);
	}
	free_paths(elements.paths);
	free_list(elements.first);
	free_files(elements.files);
	return (0);
}
