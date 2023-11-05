/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:32:58 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 19:09:48 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	plane_global(t_obj *data, t_vector ray, size_t *i, int shade)
{
	size_t	j;
	double	len_plane_next;
	double	len_plane;

	if (!data->pl)
		return (0);
	j = 0;
	len_plane = plane_intersection(data, data->pl[*i], ray, shade);
	(*i)++;
	while (data->pl[*i])
	{
		len_plane_next = plane_intersection(data, data->pl[*i], ray, shade);
		if (len_plane_next > 0)
			len_plane = cy_len(len_plane, len_plane_next, &j, i);
		(*i)++;
	}
	(*i) = j;
	return (len_plane);
}
