/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:50:37 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 14:06:59 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

char	**line_maker(t_save *list)
{
	t_save	*head;
	char	**lines;
	size_t	size;
	size_t	i;

	head = list;
	i = 0;
	size = lst_size(list);
	lines = malloc(sizeof(char *) * (size + 1));
	while (head->line)
	{
		lines[i] = ft_strdup(head->line);
		i++;
		head = head->next;
	}
	lines[i] = NULL;
	return (lines);
}

void	clear_list(t_save **list)
{
	if (!(*list))
		return ;
	if ((*list)->next)
		clear_list(&(*list)->next);
	if ((*list)->line)
		free((*list)->line);
	free(*list);
	*list = NULL;
}

t_save	*line_list(int fd)
{
	t_save	*list;
	t_save	*head;
	char	*buffer;

	list = malloc(sizeof(t_save));
	list->line = NULL;
	head = list;
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
		{
			head->line = NULL;
			head->next = NULL;
			break ;
		}
		head->line = ft_strtrim(buffer, " \r\f\t\v");
		head->next = malloc(sizeof(t_save));
		head = head->next;
		free(buffer);
	}
	return (list);
}

char	**filling_lines(char *file)
{
	t_save	*list;
	char	**file_line;
	int		fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		return (printf("%s :No such file or directory\n", file), NULL);
	list = line_list(fd);
	close(fd);
	file_line = line_maker(list);
	clear_list(&list);
	return (file_line);
}

size_t	file_size(char **str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0; 
	while (str[i])
	{
		if (ft_strncmp("\n", str[i], ft_strlen(str[i])))
			size++;
		i++;
	}
	return (size);
}
