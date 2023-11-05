/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:41:19 by markik            #+#    #+#             */
/*   Updated: 2023/11/05 17:42:23 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_vars	loading_texture(char *file)
{
	t_vars	texture;

	texture.mlx = mlx_init();
	texture.img = mlx_xpm_file_to_image(texture.mlx, file, &texture.width, \
			&texture.hight); 
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, \
			&texture.line_length, &texture.endian);
	return (texture);
}
