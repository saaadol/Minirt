/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:44:49 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 19:09:57 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	shade_intersection(t_obj *data, t_vector ray)
{
	t_cyin	in;
	double	result;

	in.i_plane = 0.0;
	in.i_sphere = 0.0;
	in.i_cylinder = 0.0;
	in.len_plane = plane_global(data, ray, &in.i_plane, 1);
	in.len_sphere = sphere_global(data, ray, &in.i_sphere, 1);
	in.len_cylinder = cylinder_global(data, ray, &in.i_cylinder, 1);
	if (!in.len_plane && !in.len_sphere && !in.len_cylinder)
		return (0.0);
	result = minpositive(__DBL_MAX__, in.len_cylinder, \
			in.len_plane, in.len_sphere);
	return (result);
}

double	shades(t_obj *data, t_vector ray_origin, t_vector normal)
{
	t_vector	hit_point;
	t_vector	z;
	t_vector	ray_direction;
	double		t;
	double		distance;

	data->c->hitpoint = vector_add(ray_origin, multi_vec_by_n(normal, EPS));
	z = making_new_vector(data->l->x, data->l->y, data->l->z);
	ray_direction = vector_subtract(z, ray_origin);
	t = vector_len(ray_direction);
	ray_direction = normalize(ray_direction);
	distance = shade_intersection(data, ray_direction);
	if (distance < 0)
		return (0);
	hit_point = vector_add(data->c->hitpoint, \
			multi_vec_by_n(ray_direction, distance));
	if (distance > 0.0 && t - \
			vector_len(vector_subtract(data->c->hitpoint, hit_point)) > 0)
		return (distance);
	return (0);
}
