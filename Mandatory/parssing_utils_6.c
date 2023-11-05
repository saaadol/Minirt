/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:48:42 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 14:52:56 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int	camera_protection(char *line)
{
	char	**splite;
	size_t	i;

	i = 0;
	splite = ft_split(line, ' ');
	if (splite_size(splite) != 4)
		return (free_double(splite), 1);
	if (ft_strncmp(splite[0], "C", 2))
		return (free_double(splite), 1);
	if (xyz_correct(splite[1]))
		return (free_double(splite), 1);
	if (xyz_vectors_correct(splite[2]))
		return (free_double(splite), 1);
	if (fov_range(splite[3]))
		return (free_double(splite), 1);
	return (free_double(splite), 0);
}

int	brightness_ratio_range(char *str)
{
	size_t	i;
	size_t	flag;
	double	num;

	flag = 0;
	i = 0;
	if (!str[i] || str[i] == '-')
		return (1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.' && flag == 0)
			flag = 1;
		else if ((str[i] < 48 || str[i] > 57) && str[i] != '\n')
			return (1);
		i++;
	}
	num = ft_atof(str);
	if (num > 1.0f)
		return (1);
	return (0);
}

int	light_protection(char *line)
{
	char	**splite;
	size_t	i;

	i = 0;
	splite = ft_split(line, ' ');
	if (splite_size(splite) != 4)
		return (free_double(splite), 1);
	if (ft_strncmp(splite[0], "L", 2))
		return (free_double(splite), 1);
	if (xyz_correct(splite[1]))
		return (free_double(splite), 1);
	if (brightness_ratio_range(splite[2]))
		return (free_double(splite), 1);
	if (check_rgb(splite[3]))
		return (free_double(splite), 1);
	return (free_double(splite), 0);
}

int	sphere_diam_correct(char *str)
{
	size_t	i;
	size_t	flag;

	flag = 0;
	i = 0;
	if (!str[i] || str[i] == '-')
		return (1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.' && flag == 0)
			flag = 1;
		else if ((str[i] < 48 || str[i] > 57) && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}
