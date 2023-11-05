/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:59:24 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 18:55:17 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_obj	*calculatebtmleft(t_obj *data)
{
	data->c->h = multi_vec_by_n(data->c->right, data->c->vpw);
	data->c->v = multi_vec_by_n(data->c->up, data->c->vph);
	data->c->btmlft = vector_subtract(data->c->origin, \
			vector_add(multi_vec_by_n(vector_add(data->c->h, data->c->v), \
					1.0 / 2.0), data->c->forward));
	return (data);
}

int	is_equal(t_vector v1, t_vector v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (1);
	return (0);
}

t_vector	get_up(t_vector forward)
{
	if (is_equal(forward, making_new_vector(0, 1, 0)))
		return (making_new_vector(0, 0, 1));
	if (is_equal(forward, making_new_vector(0, -1, 0)))
		return (making_new_vector(0, 0, -1));
	return (making_new_vector(0, 1, 0));
}

void	setup_camera(t_obj *data)
{
	double		aspect_ratio;
	t_vector	a;
	t_vector	b;

	aspect_ratio = WIDHT / HIGHT;
	data->c->origin = making_new_vector(data->c->x, data->c->y, data->c->z);
	data->c->direction = making_new_vector(data->c->x_axis, \
			data->c->y_axis, data->c->z_axis);
	data->c->forward = normalize(multi_vec_by_n(normalize(data->c->direction), \
				-1));
	a = cross(get_up(data->c->forward), data->c->forward);
	data->c->right = normalize(a);
	b = cross(data->c->forward, data->c->right);
	data->c->up = normalize(b);
	data->c->vpw = 2.0 * (tan((data->c->fov * M_PI / 180.0) / 2.0));
	data->c->vph = data->c->vpw / aspect_ratio;
	data = calculatebtmleft(data);
}
