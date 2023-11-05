/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:15:40 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 18:59:19 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_vector	calculate_ray_direction(t_obj *data, double u, double v)
{
	t_vector	scaledup;
	t_vector	scaledright;
	t_vector	ray_direction;

	scaledright = multi_vec_by_n(data->c->h, u);
	scaledup = multi_vec_by_n(data->c->v, v);
	ray_direction = normalize(vector_subtract(vector_add(vector_add(\
						data->c->btmlft, scaledup), \
					scaledright), data->c->origin));
	return (ray_direction);
}

t_vector	result_base_on_type(t_obj *data, t_vector l_d, t_cyin in, int type)
{
	t_vector	o_c;
	t_vector	uac;
	t_vector	result;
	t_vector	amc;

	amc = making_new_vector(data->a->r, data->a->g, data->a->b);
	uac = vector_add(multi_vec_by_n(amc, data->a->light_ratio), l_d);
	if (type == 1)
		o_c = making_new_vector(data->pl[in.i_plane]->r, \
				data->pl[in.i_plane]->g, data->pl[in.i_plane]->b);
	else if (type == 2)
		o_c = making_new_vector(data->cy[in.i_cylinder]->r, \
				data->cy[in.i_cylinder]->g, data->cy[in.i_cylinder]->b);
	else if (type == 3)
		o_c = making_new_vector(data->sp[in.i_sphere]->r, \
				data->sp[in.i_sphere]->g, data->sp[in.i_sphere]->b);
	uac = making_new_vector(uac.x / 255, uac.y / 255, uac.z / 255);
	o_c = making_new_vector(o_c.x / 255, o_c.y / 255, o_c.z / 255);
	result = multiple_vec_by_vec(uac, o_c);
	return (result);
}

int	ambient_lighting(t_obj *data, t_vector ray, t_cyin in, int type)
{
	t_vector	light_diffuse;
	t_vector	result;
	t_vector	ambient_color;
	int			color;

	light_diffuse = making_new_vector(0, 0, 0);
	if (type == 2)
		light_diffuse = a_light_cy(data, ray, in);
	else if (type == 3)
		light_diffuse = a_light_sp(data, ray, in);
	else if (type == 1)
		light_diffuse = a_light_pl(data, ray, in);
	else
	{
		ambient_color = making_new_vector(data->a->r, data->a->g, data->a->b);
		result = multi_vec_by_n(ambient_color, data->a->light_ratio);
		return (set_color(result.x, result.y, result.z));
	}
	result = result_base_on_type(data, light_diffuse, in, type);
	color = set_color(result.x * 255, result.y * 255, result.z * 255);
	return (color); 
}
