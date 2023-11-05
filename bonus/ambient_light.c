/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:16:23 by souledla          #+#    #+#             */
/*   Updated: 2023/11/05 19:17:03 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_vector	lighting_type(t_obj *data, t_vector ray, t_cyin in, int type)
{
	if (type == 2)
		return (cylinder_lighting(data, ray, in));
	else if (type == 3)
		return (sphere_lighting(data, ray, in));
	else if (type == 1)
		return (plane_lighting(data, ray, in));
	return (cone_lighting(data, ray, in));
}

int	ambient_lighting(t_obj *data, t_vector ray, t_cyin in, int type)
{
	t_vector	light_diffuse;
	t_vector	result;
	t_vector	ambient_color;
	int			color;

	light_diffuse = making_new_vector(0, 0, 0);
	in.i_light = 0.0;
	if (type > 0)
	{
		while (data->l[in.i_light])
		{
			light_diffuse = vector_add(light_diffuse, \
					lighting_type(data, ray, in, type));
			in.i_light++;
		}
	}
	else
	{
		ambient_color = making_new_vector(data->a->r, data->a->g, data->a->b);
		result = multi_vec_by_n(ambient_color, data->a->light_ratio);
		return (set_color(result.x, result.y, result.z));
	}
	result = result_base_on_type(data, light_diffuse, in, type);
	color = set_color(result.x * 255, result.y * 255, result.z * 255);
	return (color); 
}