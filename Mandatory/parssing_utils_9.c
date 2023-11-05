/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils_9.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:48:08 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 19:09:34 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_cy	*origin_direction(t_cy *y)
{
	y->origin = making_new_vector(y->x, y->y, y->z);
	y->direction = making_new_vector(y->x_axis, y->y_axis, y->z_axis);
	return (y);
}

t_pl	*origin_direction_pl(t_pl *y)
{
	y->origin = making_new_vector(y->x, y->y, y->z);
	y->direction = making_new_vector(y->x_axis, y->y_axis, y->z_axis);
	return (y);
}

t_cy	**filling_cy(char **line, int size, t_obj *data)
{
	t_cy	**y;
	int		i;
	char	**splite;

	if (!line)
		return (NULL);
	i = 0;
	y = malloc(sizeof(t_cy *) * (size + 1));
	while (i < size)
	{
		y[i] = malloc(sizeof(t_cy));
		splite = ft_split(line[i], ' ');
		ft_matrix(splite[1], &y[i]->x, &y[i]->y, &y[i]->z);
		ft_matrix(splite[2], &y[i]->x_axis, &y[i]->y_axis, &y[i]->z_axis);
		y[i]->cylinder_diam = ft_atof(splite[3]);
		y[i]->cylinder_height = ft_atof(splite[4]);
		ft_matrix(splite[5], &y[i]->r, &y[i]->g, &y[i]->b);
		y[i]->color = set_color(y[i]->r, y[i]->g, y[i]->b);
		y[i]->data = data;
		free_double(splite);
		y[i] = origin_direction(y[i]);
		i++;
	}
	y[i] = NULL;
	return (free_double(line), y);
}

t_pl	**filling_pl(char **line, int size, t_obj *data)
{
	t_pl	**p;
	char	**splite;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	p = malloc(sizeof(t_pl *) * (size + 1));
	while (i < size)
	{
		p[i] = malloc(sizeof(t_pl));
		splite = ft_split(line[i], ' ');
		ft_matrix(splite[1], &p[i]->x, &p[i]->y, &p[i]->z);
		ft_matrix(splite[2], &p[i]->x_axis, &p[i]->y_axis, &p[i]->z_axis);
		ft_matrix(splite[3], &p[i]->r, &p[i]->g, &p[i]->b);
		p[i]->data = data;
		free_double(splite);
		p[i] = origin_direction_pl(p[i]);
		i++;
	}
	p[i] = NULL;
	return (free_double(line), p);
}

t_sp	**filling_sp(char **line, int size, t_obj *data)
{
	t_sp	**sphere;
	char	**splite;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	sphere = malloc(sizeof(t_sp *) * (size + 1));
	while (i < size)
	{
		sphere[i] = malloc(sizeof(t_sp));
		splite = ft_split(line[i], ' ');
		ft_matrix(splite[1], &sphere[i]->x, &sphere[i]->y, &sphere[i]->z);
		sphere[i]->sphere_diam = ft_atof(splite[2]);
		ft_matrix(splite[3], &sphere[i]->r, &sphere[i]->g, &sphere[i]->b);
		sphere[i]->color = set_color(sphere[i]->r, sphere[i]->g, sphere[i]->b);
		sphere[i]->data = data;
		free_double(splite);
		sphere[i]->center = making_new_vector(sphere[i]->x, \
				sphere[i]->y, sphere[i]->z);
		i++;
	}
	sphere[i] = NULL;
	return (free_double(line), sphere);
}
