/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:39:03 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 17:44:28 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	my_mlx_pixel_put(t_obj *data, int i, int j, int color)
{
	char	*dst;

	dst = data->vars->addr + (j * data->vars->line_length + \
			i * (data->vars->bits_per_pixel / 8));
	*(int *)dst = color;
}

void	ray_tracer(t_obj *data)
{
	t_vector	ray;
	t_mabc		x;
	int			color;

	x.j = HIGHT -1;
	x.u = 0;
	x.v = 0;
	while (x.j >= 0)
	{
		x.i = 0;
		while (x.i <= WIDHT - 1.0)
		{
			x.u = (x.i / ((double) WIDHT - 1.0));
			x.v = (x.j / ((double) HIGHT - 1.0));
			ray = calculate_ray_direction(data, x.u, x.v);
			if (intersection(data, ray, &color))
				my_mlx_pixel_put(data, (int)x.i, HIGHT - (int)x.j - 1, color);
			x.i++;
		}
		x.j--;
	}
}

void	drawing_func(t_obj *data)
{
	setup_camera(data);
	ray_tracer(data);
	mlx_put_image_to_window(data->vars->mlx, \
			data->vars->win, data->vars->img, 0, 0);
}
