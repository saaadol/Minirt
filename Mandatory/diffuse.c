/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:35:04 by markik            #+#    #+#             */
/*   Updated: 2023/11/03 16:35:52 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_vector	diffuse(t_obj *data, double angle)
{
	t_vector	light;
	t_vector	diffuse;

	light = making_new_vector(data->l->r, data->l->g, data->l->b);
	if (angle > 0)
		diffuse = multi_vec_by_n(light, data->l->light_ratio * angle * 0.5);
	else
		diffuse = making_new_vector(0, 0, 0);
	return (diffuse);
}
