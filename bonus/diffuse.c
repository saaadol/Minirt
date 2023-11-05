/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:35:04 by markik            #+#    #+#             */
/*   Updated: 2023/11/05 18:58:35 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_vector	rgb_conversion(int color)
{
	t_vector	rgb_converted;

	rgb_converted = making_new_vector(0, 0, 0);
	rgb_converted.x = ((color & 0xFF0000) >> 16);
	rgb_converted.y = ((color & 0x00FF00) >> 8);
	rgb_converted.z = ((color & 0x0000FF));
	return (rgb_converted);
}

t_vector	get_texture_pixel(struct s_vars texture, t_sp *sp_data,
	t_vector hitpoint)
{
	t_vector	color_converted;
	double		a;
	double		b;
	int			x[2];

	uv_checker(sp_data, &a, &b, hitpoint);
	x[0] = floor(a * texture.width);
	x[1] = floor(b * texture.hight);
	x[0] = clamp_(x[0], 0, texture.width - 1);
	x[1] = clamp_(x[1], 0, texture.hight - 1);
	x[1] = *(unsigned int *)(texture.addr + (x[1] * texture.line_length
				+ x[0] * (texture.bits_per_pixel / 8)));
	color_converted = rgb_conversion(x[1]);
	return (color_converted);
}

t_vector	diffuse_sp(t_obj *data, double angle, t_cyin in, t_vector hitpoint)
{
	t_vector	light;
	t_vector	diffuse;

	if (data->checkboard)
		light = checkerboard_sphere(hitpoint, data->sp[in.i_sphere], data);
	else if (data->sp[in.i_sphere]->has_bumb)
		light = get_texture_pixel(data->sp[in.i_sphere]->vars,
				data->sp[in.i_sphere], hitpoint);
	else
		light = making_new_vector(data->l[in.i_light]->r,
				data->l[in.i_light]->g, data->l[in.i_light]->b);
	if (angle > 0)
		diffuse = multi_vec_by_n(light,
				data->l[in.i_light]->light_ratio * angle * 0.5);
	else
		diffuse = making_new_vector(0, 0, 0);
	return (diffuse);
}

t_vector	diffuse_cy(t_obj *data, double angle, t_cyin in, t_vector hitpoint)
{
	t_vector	light;
	t_vector	diffuse;

	if (data->checkboard)
	{
		light = checkerboard_cylinder(hitpoint, data->cy[in.i_cylinder]);
	}
	else 
		light = making_new_vector(data->l[in.i_light]->r,
				data->l[in.i_light]->g, data->l[in.i_light]->b);
	if (angle > 0)
	{
		diffuse = multi_vec_by_n(light,
				data->l[in.i_light]->light_ratio * angle * 0.5);
	}
	else
		diffuse = making_new_vector(0, 0, 0);
	return (diffuse);
}
