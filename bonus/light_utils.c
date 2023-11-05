/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:15:40 by markik            #+#    #+#             */
/*   Updated: 2023/11/05 19:16:58 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_vector	reflection(t_vector l, t_vector n)
{
	t_vector	r;

	r = vector_subtract(multi_vec_by_n(n, 2.0 * dot(l, n)), l);
	return (r);
}

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

t_vector	result_base_on_type_1(t_obj *data, t_vector l_d, \
	t_cyin in, int type)
{
	t_vector	o_c;

	if (type == 1)
	{
		if (data->checkboard)
			o_c = making_new_vector(l_d.x, l_d.y, l_d.z);
		else
			o_c = making_new_vector(data->pl[in.i_plane]->r, \
				data->pl[in.i_plane]->g, data->pl[in.i_plane]->b);
	}
	else 
	{
		if (data->checkboard)
			o_c = making_new_vector(l_d.x, l_d.y, l_d.z);
		else
			o_c = making_new_vector(data->cy[in.i_cylinder]->r, \
					data->cy[in.i_cylinder]->g, data->cy[in.i_cylinder]->b);
	}
	return (o_c);
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
		o_c = result_base_on_type_1(data, l_d, in, type);
	else if (type == 2)
		o_c = result_base_on_type_1(data, l_d, in, type);
	else if (type == 3)
	{
		if (data->checkboard)
			o_c = making_new_vector(l_d.x, l_d.y, l_d.z);
		else
			o_c = making_new_vector(data->sp[in.i_sphere]->r, \
					data->sp[in.i_sphere]->g, data->sp[in.i_sphere]->b);
	}
	else if (type == 4)
		o_c = making_new_vector(data->cn->r, data->cn->g, data->cn->b);
	uac = making_new_vector(uac.x / 255, uac.y / 255, uac.z / 255);
	o_c = making_new_vector(o_c.x / 255, o_c.y / 255, o_c.z / 255);
	result = multiple_vec_by_vec(uac, o_c);
	return (result);
}




