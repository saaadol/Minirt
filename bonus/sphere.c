/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:52:07 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 19:10:04 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	sphere_intersection(t_sp *sp_data, t_vector ray, int type)
{
	t_mabc		x;
	t_vector	cam_sphere;
	t_vector	origin;

	if (type == 0)
		origin = sp_data->data->c->origin;
	else
		origin = sp_data->data->c->hitpoint;
	cam_sphere = vector_subtract(origin, sp_data->center);
	x.a = dot(ray, ray);
	x.b = 2 * (dot(ray, cam_sphere));
	x.c = dot(cam_sphere, cam_sphere) - (sp_data->sphere_diam / \
			2) * (sp_data->sphere_diam / 2);
	x.delta = (x.b * x.b) - (4 * x.c * x.a);
	if (x.delta < 0)
		return (0);
	x.t1 = (-x.b - sqrt(x.delta)) / (2 * x.a);
	x.t2 = (-x.b + sqrt(x.delta)) / (2 * x.a);
	if (x.t1 < 0 && x.t2 < 0)
		return (0);
	if (x.t1 < 0)
		return (x.t2);
	if (x.t2 < 0)
		return (x.t1);
	return (fmin(x.t1, x.t2));
}

double	sphere_global(t_obj *data, t_vector ray, size_t *i, int shade)
{
	size_t	j;
	double	len_sphere_next;
	double	len_sphere;

	if (!data->sp)
		return (0);
	j = 0;
	len_sphere = sphere_intersection(data->sp[*i], ray, shade);
	(*i)++;
	while (data->sp[*i])
	{
		len_sphere_next = sphere_intersection(data->sp[*i], ray, shade);
		if (len_sphere_next > 0)
			len_sphere = cy_len(len_sphere, len_sphere_next, &j, i);
		(*i)++;
	}
	(*i) = j;
	return (len_sphere);
}
