/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:14:11 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/17 20:48:08 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static void	create_heredoc_name(t_elements *elements)
{
	int		i;
	char	*here_doc;

	i = 1;
	here_doc = ft_strdup(".here_doc");
	elements->here_doc = ft_strjoin(here_doc, "");
	if (!elements->here_doc)
		error("Cannot create here_doc temporary file", elements);
	while (!access(elements->here_doc, F_OK))
	{
		free(elements->here_doc);
		elements->here_doc = ft_join_and_free_1(here_doc, ft_itoa(i), 0, 1);
		if (!elements->here_doc)
		{
			free(here_doc);
			perror("Cannot create here_doc temporary file");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	free(here_doc);
}

void	here_doc(char *limiter, t_elements *elements)
{
	int		fd;
	int		loop;
	char	*content;

	loop = 1;
	create_heredoc_name(elements);
	limiter = ft_strjoin(limiter, "\n");
	if (!limiter)
		error("here_doc : ft_strjoin", elements);
	fd = open(elements->here_doc, O_RDONLY | O_TRUNC | O_CREAT, 0777);
	if (fd < 0)
		error("Cannot create here_doc temporary file", elements);
	while (loop)
	{
		content = get_next_line(STDIN_FILENO);
		if (!content || !*content || !ft_strcmp(content, limiter))
			loop = 0;
		else
			ft_putstr_fd(content, fd);
		free(content);
	}
	free(limiter);
	free(elements->files[0]);
	elements->files[0] = elements->here_doc;
	close(fd);
}
