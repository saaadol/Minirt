/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:03:04 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 18:15:09 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_vector	reflection(t_vector l, t_vector n)
{
	t_vector	r;

	r = vector_subtract(multi_vec_by_n(n, 2.0 * dot(l, n)), l);
	return (r);
}

t_vector	specular(t_obj *data, t_vector l, t_vector n, t_vector v)
{
	t_vector	r;
	double		d;

	r = reflection(l, n);
	d = pow(fmax(0.0, dot(r, v)), 32);
	return (multi_vec_by_n(making_new_vector(data->l->r, \
					data->l->g, data->l->b), data->l->light_ratio * d));
}

t_vector	a_light_cy(t_obj *data, t_vector ray, t_cyin in)
{
	double		angle;
	t_vector	a;
	t_vector	z;
	t_vector	az;

	a = vector_add(data->c->origin, multi_vec_by_n(ray, in.len_cylinder));
	z = making_new_vector(data->l->x, data->l->y, data->l->z);
	az = normalize(vector_subtract(z, a));
	angle = dot(az, data->cy[in.i_cylinder]->interssection_direction);
	if (shades(data, a, data->cy[in.i_cylinder]->interssection_direction))
		return (making_new_vector(0, 0, 0));
	return (vector_add(diffuse(data, angle), specular(data, \
					az, data->cy[in.i_cylinder]->interssection_direction, \
					normalize(vector_subtract(data->c->origin, a)))));
}

t_vector	a_light_sp(t_obj *data, t_vector ray, t_cyin in)
{
	double		angle;
	t_vector	a;
	t_vector	ea;
	t_vector	z;
	t_vector	az;

	a = vector_add(data->c->origin, multi_vec_by_n(ray, in.len_sphere));
	ea = normalize(vector_subtract(a, data->sp[in.i_sphere]->center));
	z = making_new_vector(data->l->x, data->l->y, data->l->z);
	az = normalize(vector_subtract(z, a));
	angle = dot(az, ea);
	if (shades(data, a, az))
		return (making_new_vector(0, 0, 0));
	return (vector_add(diffuse(data, angle), specular(data, \
					az, ea, normalize(vector_subtract(data->c->origin, a)))));
}

t_vector	a_light_pl(t_obj *data, t_vector ray, t_cyin in)
{
	double		angle;
	t_vector	a;
	t_vector	z;
	t_vector	az;

	if (dot(data->pl[in.i_plane]->direction, ray) > 0)
		data->pl[in.i_plane]->direction = multi_vec_by_n(\
				data->pl[in.i_plane]->direction, -1);
	a = vector_add(data->c->origin, multi_vec_by_n(ray, in.len_plane));
	z = making_new_vector(data->l->x, data->l->y, data->l->z);
	az = normalize(vector_subtract(z, a));
	angle = dot(az, data->pl[in.i_plane]->direction);
	if (shades(data, a, data->pl[in.i_plane]->direction))
		return (making_new_vector(0, 0, 0));
	return (vector_add(diffuse(data, angle), specular(data, \
					az, normalize(data->pl[in.i_plane]->direction), \
					normalize(vector_subtract(data->c->origin, a)))));
}
