/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:27 by markik            #+#    #+#             */
/*   Updated: 2023/11/05 15:40:56 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static t_mabc	calculate_delta(t_obj *data, t_cn *cone, t_vector r_d, int type)
{
	t_vector	origin;
	t_vector	cone_normal;
	t_vector	oc;
	t_mabc		in;

	if (type == 0)
		origin = data->c->origin;
	else
		origin = data->c->hitpoint;
	cone_normal = normalize(cone->direction);
	oc = vector_subtract(origin, cone->origin);
	in.m = pow(cone->cone_diam / 2.0, 2) / pow(cone->cone_height, 2);
	in.a = dot(r_d, r_d) - (1 + in.m) * \
		pow(dot(r_d, cone_normal), 2);
	in.b = dot(r_d, oc) - dot(r_d, cone_normal) * \
		dot(oc, cone_normal) * (1 + in.m) + in.m * \
		cone->cone_height * dot(r_d, cone_normal);
	in.c = dot(oc, oc) - pow(dot(oc, cone_normal), 2) * \
		(1 + in.m) - pow(cone->cone_diam / 2, 2) + 2 * \
		in.m * cone->cone_height * dot(oc, cone_normal);
	in.delta = pow(in.b, 2) - in.a * in.c;
	return (in);
}

double	coneintersectio(t_obj *data, t_cn *cone, t_vector direction, int type)
{
	t_mabc	in;

	in = calculate_delta(data, cone, direction, type);
	if (in.delta < 0)
		return (0);
	in.t1 = (-in.b - sqrt(in.delta)) / in.a; 
	in.t2 = (-in.b + sqrt(in.delta)) / in.a; 
	if (in.t1 < 0 && in.t2 < 0)
		return (0);
	if (in.t1 < 0)
		return (in.t2);
	if (in.t2 < 0)
		return (in.t1);
	return (fmin(in.t1, in.t2));
}

double	getcone(t_obj *data, t_cn *cone, t_vector direction, int type)
{
	t_vector	cone_normal;
	t_vector	hitpoint;
	t_vector	origin; 
	double		t;
	double		d;

	if (type == 0)
		origin = data->c->origin;
	else
		origin = data->c->hitpoint;
	cone_normal = normalize(cone->direction); 
	t = coneintersectio(data, cone, direction, type);
	if (t > 0)
	{
		hitpoint = vector_add(origin, multi_vec_by_n(direction, t));
		d = dot(vector_subtract(hitpoint, cone->origin), cone_normal);
		if (d < 0 || d > cone->cone_height)
			return (0);
		cone->interssection_direction = normalize(vector_subtract(hitpoint, \
					vector_add(cone->origin, multi_vec_by_n (cone_normal, d))));
		return (t);
	}
	return (0);
}

double	conebtm(t_obj *data, t_cn *cone, t_vector r, int type)
{
	t_vector	hitpoint;
	t_vector	origin;
	t_pl		p;
	double		t;
	double		y;

	if (type == 0)
		origin = data->c->origin;
	else
		origin = data->c->hitpoint;
	p.origin = cone->origin;
	p.direction = normalize(multi_vec_by_n(cone->direction, -1));
	t = plane_intersection(data, &p, r, type);
	if (t > 0)
	{
		hitpoint = vector_add(origin, multi_vec_by_n(r, t));
		y = vector_len(vector_subtract(hitpoint, cone->origin));
		if (pow(y, 2) > pow(cone->cone_diam / 2.0, 2))
			return (0);
		cone->interssection_direction = p.direction;
		return (t);
	}
	return (0);
}

double	cone_top_btm(t_obj *data, t_cn *cone, t_vector direction, int type)
{
	double		cy;
	double		btm;
	double		result;
	t_vector	cy_;
	t_vector	btm_;

	if (!cone)
		return (0);
	cy = getcone(data, cone, direction, type);
	cy_ = making_new_vector (cone->interssection_direction.x, \
			cone->interssection_direction.y, cone->interssection_direction.z);
	btm = conebtm(data, cone, direction, type);
	btm_ = making_new_vector (cone->interssection_direction.x, \
			cone->interssection_direction.y, cone->interssection_direction.z);
	if (!cy && !btm)
		return (0);
	result = minpositive(cy, btm, __DBL_MAX__, __DBL_MAX__);
	if (result == cy)
		cone->interssection_direction = making_new_vector(cy_.x, cy_.y, cy_.z);
	else if (result == btm)
		cone->interssection_direction = making_new_vector(btm_.x, \
				btm_.y, btm_.z);
	return (result);
}
