/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:36:09 by markik            #+#    #+#             */
/*   Updated: 2023/11/05 17:38:22 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int	controling_windows_man(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		free_struct(vars->data);
		mlx_destroy_image(vars->mlx, vars->img);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	exit_(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

void	exec_part(t_obj *data)
{
	data->vars = malloc(sizeof(t_vars));
	data->vars->data = data;
	data->vars->mlx = mlx_init();
	data->vars->win = mlx_new_window(data->vars->mlx, \
			WIDHT, HIGHT, PROJET_NAME);
	data->vars->img = mlx_new_image(data->vars->mlx, \
			WIDHT, HIGHT);
	data->vars->addr = mlx_get_data_addr(data->vars->img, \
			&data->vars->bits_per_pixel, \
			&data->vars->line_length, &data->vars->endian);
	drawing_func(data);
	mlx_hook((data->vars)->win, 2, (1L << 0), \
			controling_windows_man, data->vars);
	mlx_hook((data->vars)->win, 17, 0, exit_, data->vars);
	mlx_loop((data->vars)->mlx);
}
