/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:18:45 by markik            #+#    #+#             */
/*   Updated: 2023/11/03 16:34:24 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static t_mabc	calculate_cylinder(t_obj *data, t_cy *y, t_vector r_d, int type)
{
	t_vector	origin;
	t_mabc		in;
	t_vector	w;

	if (type == 0)
		origin = data->c->origin;
	else
		origin = data->c->hitpoint;
	y->bottom_vector = vector_add(y->origin, \
			multi_vec_by_n(normalize(y->direction), \
				- (y->cylinder_height / 2)));
	w = vector_subtract(origin, y->bottom_vector);
	in.a = dot(r_d, r_d) - pow(dot(r_d, normalize(y->direction)), 2);
	in.b = 2 * (dot(r_d, w) - (dot(r_d, normalize(y->direction)) * \
				dot(w, normalize(y->direction))));
	in.c = dot(w, w) - pow(dot(w, normalize(y->direction)), 2) - \
		pow(y->cylinder_diam / 2, 2);
	in.delta = pow(in.b, 2) - (4 * in.a * in.c);
	return (in);
}

double	cylinderintersectio(t_obj *data, t_cy *cy_data, t_vector r_d, int type)
{
	t_mabc	in;

	in = calculate_cylinder(data, cy_data, r_d, type);
	if (in.delta < 0)
		return (-1);
	in.t1 = (-in.b - sqrt(in.delta)) / (2 * in.a);
	in.t2 = (-in.b + sqrt(in.delta)) / (2 * in.a);
	if (in.t1 < 0 && in.t2 < 0)
		return (-1);
	if (in.t1 < 0)
		return (in.t2);
	if (in.t2 < 0)
		return (in.t1);
	return (fmin(in.t1, in.t2));
}

double	cy_len(double l_cy, double l_cy_next, size_t *j, size_t *i)
{
	double	len;

	if (!l_cy)
	{
		l_cy = l_cy_next;
		*j = *i;
	}
	else
	{
		len = fmin(l_cy_next, l_cy);
		if (len == l_cy_next)
		{
			l_cy = l_cy_next;
			*j = *i;
		}
	}
	return (l_cy);
}

double	cylinder_global(t_obj *data, t_vector ray, size_t *i, int shade)
{
	size_t	j;
	double	len_cylinder_next;
	double	len_cylinder;

	if (!data->cy)
		return (0);
	j = 0;
	len_cylinder = cy_top_btm(data, data->cy[*i], ray, shade);
	(*i)++;
	while (data->cy[*i])
	{
		len_cylinder_next = cy_top_btm(data, data->cy[*i], ray, shade);
		if (len_cylinder_next > 0)
			len_cylinder = cy_len(len_cylinder, len_cylinder_next, &j, i);
		(*i)++;
	}
	(*i) = j;
	return (len_cylinder);
}
