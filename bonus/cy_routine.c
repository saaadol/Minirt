/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:24:55 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 18:55:30 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	getcylinder(t_obj *data, t_cy *y, t_vector direction, int type)
{
	t_vector	hitpoint;
	t_vector	origin;
	double		t;
	double		d;

	if (type == 0)
		origin = data->c->origin;
	else
		origin = data->c->hitpoint;
	y->direction = normalize(y->direction);
	t = cylinderintersectio(data, y, direction, type);
	if (t > 0)
	{
		hitpoint = vector_add(origin, multi_vec_by_n(direction, t));
		d = dot(normalize(y->direction), \
				vector_subtract(hitpoint, y->bottom_vector));
		if (d < 0 || d > y->cylinder_height)
			return (0);
		y->interssection_direction = \
			normalize(vector_subtract(vector_subtract(hitpoint, \
			y->origin), multi_vec_by_n(y->direction, \
			dot(vector_subtract(hitpoint, y->origin), y->direction))));
		return (t);
	}
	return (0);
}

t_pl	f_p_cy(t_cy *y)
{
	t_pl	p;

	y->upper_vector = vector_add(y->origin, multi_vec_by_n(\
				normalize(y->direction), y->cylinder_height / 2));
	p.origin = making_new_vector(y->upper_vector.x, \
			y->upper_vector.y, y->upper_vector.z);
	p.direction = normalize(making_new_vector(y->direction.x, \
				y->direction.y, y->direction.z));
	return (p);
}

double	cylindertop(t_obj *data, t_cy *y, t_vector r_y, int type)
{
	t_vector	hitpoint;
	t_vector	origin;
	t_pl		p;
	double		t;

	if (type == 0)
		origin = data->c->origin;
	else
		origin = data->c->hitpoint;
	p = f_p_cy(y);
	t = plane_intersection(data, &p, r_y, type);
	if (t > 0)
	{
		hitpoint = vector_add(origin, multi_vec_by_n(r_y, t));
		if (vector_len(vector_subtract(hitpoint, \
						y->upper_vector)) > y->cylinder_diam / 2.0)
			return (0);
		y->interssection_direction = making_new_vector(p.direction.x, \
				p.direction.y, p.direction.z);
		return (t);
	}
	return (0);
}

double	cylinderbtm(t_obj *data, t_cy *y, t_vector r_y, int type)
{
	t_vector	hitpoint;
	t_vector	origin;
	t_pl		p;
	double		t;
	double		area;

	if (type == 0)
		origin = data->c->origin;
	else
		origin = data->c->hitpoint;
	p.origin = making_new_vector(y->bottom_vector.x, \
			y->bottom_vector.y, y->bottom_vector.z);
	p.direction = multi_vec_by_n(normalize(making_new_vector(y->direction.x, \
					y->direction.y, y->direction.z)), (-1));
	t = plane_intersection(data, &p, r_y, type);
	if (t > 0)
	{
		hitpoint = vector_add(origin, multi_vec_by_n(r_y, t));
		area = pow(vector_len(vector_subtract(hitpoint, y->bottom_vector)), 2);
		if (area >= pow(y->cylinder_diam / 2.0, 2))
			return (0);
		return (y->interssection_direction = making_new_vector(p.direction.x, \
				p.direction.y, p.direction.z), t);
	}
	return (0);
}

double	cy_top_btm(t_obj *data, t_cy *y, t_vector direction, int type)
{
	t_cyin	x;
	double	cy;
	double	top;
	double	btm;
	double	result;

	cy = getcylinder(data, y, direction, type);
	x.cy = making_new_vector(y->interssection_direction.x, \
			y->interssection_direction.y, y->interssection_direction.z);
	top = cylindertop(data, y, direction, type);
	x.top = making_new_vector(y->interssection_direction.x, \
			y->interssection_direction.y, y->interssection_direction.z);
	btm = cylinderbtm(data, y, direction, type);
	x.btm = making_new_vector(y->interssection_direction.x, \
			y->interssection_direction.y, y->interssection_direction.z);
	result = minpositive(cy, top, btm, __DBL_MAX__);
	if (result == cy)
		return (y->interssection_direction = making_new_vector(x.cy.x, \
				x.cy.y, x.cy.z), result);
	else if (result == top)
		return (y->interssection_direction = making_new_vector(x.top.x, \
				x.top.y, x.top.z), result);
	return (y->interssection_direction = making_new_vector(x.btm.x, \
				x.btm.y, x.btm.z), result);
}
