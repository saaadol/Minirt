/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:44:22 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 18:55:38 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	minpositive(double a, double b, double c, double d)
{
	double	min;

	min = __DBL_MAX__;
	if (a > 0.0 && a < min)
		min = a;
	if (b > 0.0 && b < min)
		min = b;
	if (c > 0.0 && c < min)
		min = c;
	if (d > 0.0 && d < min)
		min = d;
	if (min == __DBL_MAX__)
		return (0.0);
	return (min);
}

int	intersection(t_obj *data, t_vector ray, int *color)
{
	t_cyin	in;
	double	result;

	in.i_cylinder = 0.0;
	in.i_plane = 0.0;
	in.i_sphere = 0.0;
	in.len_plane = plane_global(data, ray, &in.i_plane, 0);
	in.len_sphere = sphere_global(data, ray, &in.i_sphere, 0);
	in.len_cylinder = cylinder_global(data, ray, &in.i_cylinder, 0);
	if (!in.len_plane && !in.len_sphere && !in.len_cylinder)
		return ((*color) = ambient_lighting(data, ray, in, 0), 1);
	result = minpositive(__DBL_MAX__, in.len_cylinder, \
			in.len_plane, in.len_sphere);
	if (result == in.len_plane) 
		*color = ambient_lighting(data, ray, \
				in, 1);
	else if (result == in.len_cylinder)
		*color = ambient_lighting(data, ray, \
				in, 2);
	else if (result == in.len_sphere)
		*color = ambient_lighting(data, ray, \
				in, 3);
	return (1);
}
