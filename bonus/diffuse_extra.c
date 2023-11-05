/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:48:16 by souledla          #+#    #+#             */
/*   Updated: 2023/11/05 19:08:55 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_sp	*sphere_tools(t_sp *sphere, char **splite)
{
	sphere->has_bumb = 0;
	if (splite_size(splite) == 5)
	{
		sphere->has_bumb = 1;
		sphere->vars = loading_texture(splite[4]);
	}
	return (sphere);
}

int	check_bumb(char *file)
{
	int	fd;
	int	i;

	i = ft_strlen(file) - 1;
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		return (0);
	if (i - 3 >= 0)
	{
		if (file[i - 3] == '.' && file[i - 2] == 'x' \
		&& file[i - 1] == 'p' && file[i] == 'm')
			return (close(fd), 1);
	}
	return (close(fd), 0);
}

int	check_board(char *file)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(file, '/');
	while (split[i])
	{
		if (!ft_strncmp(split[i], "Checkboard", 11) && split[i + 1])
			return (1);
		i++;
	}
	free_double(split);
	return (0);
}

t_vector	diffuse(t_obj *data, double angle, t_cyin in)
{
	t_vector	light;
	t_vector	diffuse;

	light = making_new_vector(data->l[in.i_light]->r, \
		data->l[in.i_light]->g, data->l[in.i_light]->b);
	if (angle > 0)
		diffuse = multi_vec_by_n(light, \
		data->l[in.i_light]->light_ratio * angle * 0.5);
	else
		diffuse = making_new_vector(0, 0, 0);
	return (diffuse);
}

t_vector	checkerboard_cylinder(t_vector hitpoint, t_cy *cy_data)
{
	t_vector	light;
	double		constant;

	constant = 0.2;
	if ((int)((floor(hitpoint.x * constant) \
		+ floor(hitpoint.y * constant))) % 2 == 0)
		light = making_new_vector(255, 255, 255);
	else
		light = making_new_vector(cy_data->r, cy_data->g, cy_data->b);
	return (light);
}
