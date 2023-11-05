/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:03:04 by markik            #+#    #+#             */
/*   Updated: 2023/11/05 18:30:49 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_vector	specular(t_vector l, t_vector n, t_vector v, t_cyin in)
{
	t_vector	r;
	double		d;

	r = reflection(l, n);
	d = pow(fmax(0.0, dot(r, v)), 32);
	return (multi_vec_by_n(making_new_vector(in.data->l[in.i_light]->r, \
					in.data->l[in.i_light]->g, in.data->l[in.i_light]->b), \
				in.data->l[in.i_light]->light_ratio * d));
}

t_vector	cylinder_lighting(t_obj *data, t_vector ray, t_cyin in)
{
	double		angle;
	t_vector	a;
	t_vector	z;
	t_vector	az;

	in.data = data;
	a = vector_add(data->c->origin, multi_vec_by_n(ray, in.len_cylinder));
	z = making_new_vector(data->l[in.i_light]->x, \
			data->l[in.i_light]->y, data->l[in.i_light]->z);
	az = normalize(vector_subtract(z, a));
	angle = dot(az, data->cy[in.i_cylinder]->interssection_direction);
	if (shades(data, a, \
				data->cy[in.i_cylinder]->interssection_direction, \
				in.i_light))
		return (making_new_vector(0, 0, 0));
	return (vector_add(diffuse_cy(data, angle, in, a), \
				specular(az, data->cy[in.i_cylinder]->interssection_direction, \
					normalize(vector_subtract(data->c->origin, a)), in))); 
}

t_vector	sphere_lighting(t_obj *data, t_vector ray, t_cyin in)
{
	double		angle;
	t_vector	a;
	t_vector	z;
	t_vector	az;
	t_vector	ea;

	in.data = data;
	a = vector_add(data->c->origin, multi_vec_by_n(ray, in.len_sphere));
	ea = normalize(vector_subtract(a, data->sp[in.i_sphere]->center));
	z = making_new_vector(data->l[in.i_light]->x, \
			data->l[in.i_light]->y, data->l[in.i_light]->z);
	az = normalize(vector_subtract(z, a));
	angle = dot(az, ea);
	if (shades(data, a, az, in.i_light))
		return (making_new_vector(0, 0, 0));
	return (vector_add(diffuse_sp(data, angle, in, a), \
				specular(az, ea, normalize(vector_subtract(data->c->origin, \
							a)), in)));
}

t_vector	plane_lighting(t_obj *data, t_vector ray, t_cyin in)
{
	double		angle;
	t_vector	a;
	t_vector	z;
	t_vector	az;

	in.data = data;
	if (dot(data->pl[in.i_plane]->direction, ray) > 0)
		data->pl[in.i_plane]->direction = multi_vec_by_n(\
				data->pl[in.i_plane]->direction, -1);
	a = vector_add(data->c->origin, multi_vec_by_n(ray, in.len_plane));
	z = making_new_vector(data->l[in.i_light]->x, \
			data->l[in.i_light]->y, data->l[in.i_light]->z);
	az = normalize(vector_subtract(z, a));
	angle = dot(az, data->pl[in.i_plane]->direction);
	if (shades(data, a, data->pl[in.i_plane]->direction, in.i_light))
		return (making_new_vector(0, 0, 0));
	return (vector_add(diffuse_pl(data, angle, in, a), \
				specular(az, normalize(data->pl[in.i_plane]->direction), \
					normalize(vector_subtract(data->c->origin, a)), in)));
}

t_vector	cone_lighting(t_obj *data, t_vector ray, t_cyin in)
{
	double		angle;
	t_vector	a;
	t_vector	z;
	t_vector	az;

	in.data = data;
	a = vector_add(data->c->origin, multi_vec_by_n(ray, in.len_cone));
	z = making_new_vector(data->l[in.i_light]->x, \
			data->l[in.i_light]->y, data->l[in.i_light]->z);
	az = normalize(vector_subtract(z, a));
	angle = dot(az, data->cn->interssection_direction);
	if (shades(data, a, data->cn->interssection_direction, in.i_light))
		return (making_new_vector(0, 0, 0));
	return (vector_add(diffuse(data, angle, in), \
				specular(az, data->cn->interssection_direction, \
					normalize(vector_subtract(data->c->origin, a)), in)));
}
