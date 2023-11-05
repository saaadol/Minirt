/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:42:44 by markik            #+#    #+#             */
/*   Updated: 2023/11/05 15:57:29 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int	find_twins_elements(char **file_line, char *twin)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (file_line[i])
	{
		if (!ft_strncmp(file_line[i], twin, ft_strlen(twin)))
			size++;
		i++;
	}
	return (size);
}

char	**finding_multiple_element(int *len, char **file_line, char *twin)
{
	char	**stockage;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = find_twins_elements(file_line, twin);
	if (size == 0)
		return (NULL);
	stockage = malloc(sizeof(char *) * (size + 1));
	while (file_line[i])
	{
		if (!ft_strncmp(file_line[i], twin, ft_strlen(twin)))
		{
			stockage[j] = ft_strdup(file_line[i]);
			j++;
		}
		i++;
	}
	stockage[j] = NULL;
	*len = size;
	return (stockage);
}

t_obj	*filling_data(char **file_line, t_obj *data)
{
	char	**line_stockage;
	int		size;
	int		i;

	i = 0;
	size = 0;
	if (!searching_for(file_line, "A") || !searching_for(file_line, \
				"C") || !searching_for(file_line, "L"))
		return (NULL);
	data->a = filling_a(searching_for(file_line, "A"));
	data->a->data = data;
	data->c = filling_c(searching_for(file_line, "C"));
	data->c->data = data;
	data->l = filling_l(searching_for(file_line, "L"));
	data->l->data = data;
	line_stockage = finding_multiple_element(&size, file_line, "cy");
	data->cy = filling_cy(line_stockage, size, data);
	line_stockage = finding_multiple_element(&size, file_line, "pl");
	data->pl = filling_pl(line_stockage, size, data);
	line_stockage = finding_multiple_element(&size, file_line, "sp");
	data->sp = filling_sp(line_stockage, size, data);
	return (data);
}

int	parssing(char *file, t_obj *data)
{
	char	**file_line;
	int		error;
	char	**stock;

	if (type_check(file))
		return (99);
	stock = filling_lines(file);
	if (!stock)
		return (98);
	file_line = remove_line_break(stock);
	remove_multiple_space(file_line);
	error = protections(file_line);
	if (error)
		return (free_double(file_line), error);
	data = filling_data(file_line, data);
	if (!data)
		return (free_double(file_line), 8);
	return (free_double(file_line), 0);
}
