/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils_8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:43:55 by markik            #+#    #+#             */
/*   Updated: 2023/11/05 15:09:55 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

char	*searching_for(char **file_line, char *type)
{
	char	**buffer;
	size_t	i;

	i = 0;
	while (file_line[i])
	{
		buffer = ft_split(file_line[i], ' ');
		if (!ft_strncmp(buffer[0], type, ft_strlen(type)))
			return (free_double(buffer), file_line[i]);
		free_double(buffer);
		i++;
	}
	return (NULL);
}

t_a	*filling_a(char *line)
{
	t_a		*ambient_lightning;
	char	**splite;
	char	**matrix;

	if (!line)
		return (NULL);
	ambient_lightning = malloc(sizeof(t_a));
	splite = ft_split(line, ' ');
	ambient_lightning->light_ratio = ft_atof(splite[1]);
	matrix = ft_split(splite[2], ',');
	ambient_lightning->r = ft_atof(matrix[0]);
	ambient_lightning->g = ft_atof(matrix[1]);
	ambient_lightning->b = ft_atof(matrix[2]);
	ambient_lightning->color = set_color(ambient_lightning->r, \
			ambient_lightning->g, ambient_lightning->b);
	free_double(splite);
	free_double(matrix);
	return (ambient_lightning);
}

t_c	*filling_c(char *line)
{
	t_c		*camera;
	char	**splite;
	char	**matrix;

	if (!line)
		return (NULL);
	camera = malloc(sizeof(t_c));
	splite = ft_split(line, ' ');
	matrix = ft_split(splite[1], ',');
	camera->x = ft_atof(matrix[0]);
	camera->y = ft_atof(matrix[1]);
	camera->z = ft_atof(matrix[2]);
	free_double(matrix);
	matrix = ft_split(splite[2], ',');
	camera->x_axis = ft_atof(matrix[0]);
	camera->y_axis = ft_atof(matrix[1]);
	camera->z_axis = ft_atof(matrix[2]);
	free_double(matrix);
	camera->fov = ft_atof(splite[3]);
	free_double(splite);
	return (camera);
}

t_l	*filling_l(char *line)
{
	t_l		*light;
	char	**splite;
	char	**matrix;

	if (!line)
		return (NULL);
	light = malloc(sizeof(t_l));
	splite = ft_split(line, ' ');
	matrix = ft_split(splite[1], ',');
	light->x = ft_atof(matrix[0]);
	light->y = ft_atof(matrix[1]);
	light->z = ft_atof(matrix[2]);
	free_double(matrix);
	light->light_ratio = ft_atof(splite[2]);
	matrix = ft_split(splite[3], ',');
	light->r = ft_atof(matrix[0]);
	light->g = ft_atof(matrix[1]);
	light->b = ft_atof(matrix[2]);
	light->color = set_color(light->r, light->g, light->b);
	free_double(matrix);
	free_double(splite);
	return (light);
}
