/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:57:57 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 18:02:35 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_vector	multi_vec_by_n(t_vector vec, double n)
{
	t_vector	vector;

	vector = making_new_vector(vec.x * n, vec.y * n, vec.z * n);
	return (vector);
}

t_vector	cross(t_vector v1, t_vector v2)
{
	t_vector	vector;

	vector = making_new_vector(v1.y * v2.z - v1.z * v2.y, v1.z \
			* v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	return (vector);
}

t_vector	multiple_vec_by_vec(t_vector v1, t_vector v2)
{
	t_vector	vector;

	vector = making_new_vector((v1.x * v2.x), (v1.y * v2.y), (v1.z * v2.z));
	return (vector);
}

double	dot(t_vector v1, t_vector v2)
{
	double	distance;

	distance = ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
	return (distance);
}
