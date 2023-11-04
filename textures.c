/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:38:24 by souledla          #+#    #+#             */
/*   Updated: 2023/11/04 18:27:00 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h" 

t_vector	rgb_conversion(int color)
{
	t_vector	rgb_converted = making_new_vector(0,0,0);

	rgb_converted.x = ((color & 0xFF0000) >> 16) ;
	rgb_converted.y = ((color & 0x00FF00) >> 8) ;
	rgb_converted.z = ((color & 0x0000FF));
	return (rgb_converted);
}
int	clamp_(int v, int min, int max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

struct s_vars loading_texture(struct s_vars *data)
{
    struct s_vars texture;
    texture.mlx = data->mlx;
    texture.img = mlx_xpm_file_to_image(texture.mlx,"mars.xpm", &texture.width, &texture.height);
    if (!texture.img)
    {
        printf("failed");
        exit(1);
    }
    texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
    return(texture);


}
t_vector get_texture_pixel(struct s_vars texture, t_sp *sp_data, t_vector hitpoint)
{
    t_vector color_converted;
    double a;
    double b;
    int x;
    int y;
    int color;
    uv_checker(sp_data, &a, &b, hitpoint);
    x = floor(a * texture.width);
    y = floor(b * texture.height);
    x = clamp_(x, 0, texture.width - 1);
    y = clamp_(y, 0, texture.height - 1);
    
    color =  *(unsigned int *)(texture.addr + (y * texture.line_length + x * (texture.bits_per_pixel / 8)));
    color_converted = rgb_conversion(color);
    return color_converted;
}
