/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_extra2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:48:50 by souledla          #+#    #+#             */
/*   Updated: 2023/11/05 19:09:00 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_vector	checkerboard_plane(t_vector hitpoint, t_pl *pl_data)
{
	t_vector	light;
	double		constant;

	constant = 0.1;
	if ((int)((floor(hitpoint.x * constant + EPS) + floor(hitpoint.y * constant \
	+ EPS) + floor(hitpoint.z * constant + EPS))) % 2 == 0)
		light = making_new_vector(pl_data->r, pl_data->g, pl_data->b);
	else
		light = making_new_vector(255, 255, 255);
	return (light);
}

t_vector	diffuse_pl(t_obj *data, double angle, t_cyin in, t_vector hitpoint)
{
	t_vector	light;
	t_vector	diffuse;

	if (data->checkboard)
	{
		light = checkerboard_plane(hitpoint, data->pl[in.i_plane]);
	}
	else 
		light = making_new_vector(data->l[in.i_light]->r, \
		data->l[in.i_light]->g, data->l[in.i_light]->b);
	if (angle > 0)
	{
		diffuse = multi_vec_by_n(light, \
		data->l[in.i_light]->light_ratio * angle * 0.5);
	}
	else
		diffuse = making_new_vector(0, 0, 0);
	return (diffuse);
}

void	uv_checker(t_sp *data_sp, double *u, double *v, t_vector hitpoint)
{
	double	x;
	double	y;

	x = atan2(hitpoint.x, hitpoint.z) / (2 * M_PI); 
	y = acos(hitpoint.y / (data_sp->sphere_diam / 2));
	*u = 1.0 - (x + 0.5);
	*v = 1.0 - y / M_PI;
}

t_vector	checkerboard_sphere(t_vector hitpoint, t_sp *sp_data, t_obj *data)
{
	t_vector	light; 
	double		u;
	double		v;
	int			x[2];

	uv_checker(sp_data, &u, &v, hitpoint);
	x[0] = 16 * u;
	x[1] = 8 * v;
	if (data->checkboard)
	{
		if ((x[0] + x[1]) % 2 == 0)
			light = making_new_vector(sp_data->r, sp_data->g, sp_data->b);
		else
			light = making_new_vector(255, 255, 255);
	}
	else 
		light = making_new_vector(255, 255, 255);
	return (light);
}

int	clamp_(int v, int min, int max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}
