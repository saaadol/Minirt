/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:07:50 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 14:10:22 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	free_double(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	**remove_line_break(char **file_name)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	size = file_size(file_name);
	str = malloc(sizeof(char *) * (size + 1));
	while (file_name[i])
	{
		if (ft_strncmp("\n", file_name[i], ft_strlen(file_name[i])))
		{
			str[j] = ft_strdup(file_name[i]);
			j++;
		}
		i++;
	}
	str[j] = NULL;
	free_double(file_name);
	return (str);
}

int	multi_space(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 32 && line[i + 1] == 32)
			return (1);
		i++;
	}
	return (0);
}

size_t	no_multi_space_size(char *line)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (line[i])
	{
		if (line[i] == 32 && line[i + 1] == 32)
			size++;
		i++;
	}
	return (i - size);
}
