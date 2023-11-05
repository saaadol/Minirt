/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:31:01 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 16:32:23 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	plane_intersection(t_obj *data, t_pl *p, t_vector ray, int type)
{
	t_vector	plane_direction;
	t_vector	origin;
	double		t;
	double		distance1;
	double		distance2;

	if (type == 0)
		origin = data->c->origin;
	else
		origin = data->c->hitpoint;
	plane_direction = normalize(p->direction);
	t = dot(ray, plane_direction);
	if (t != 0)
	{
		distance1 = dot(vector_subtract(origin, p->origin), plane_direction);
		distance2 = -distance1 / t;
		if (distance2 < EPS)
			return (0);
		return (distance2);
	}
	return (0);
}
