/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:37:15 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 19:08:48 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int	check_num_beta(char *str, size_t *i)
{
	int	flag;

	flag = 0;
	if (!str[*i] || str[*i] == ',' || str[*i] == '.')
		return (1);
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	if (!str[*i] || str[*i] == ',' || str[*i] == '.')
		return (1);
	while (str[*i])
	{
		if (str[*i] == ',')
			return ((*i)--, 0);
		else if (str[*i] == '.' && flag == 0)
			flag = 1;
		else if (str[*i] < 48 || str[*i] > 57)
			return (1);
		(*i)++;
	}
	(*i)--;
	return (0);
}

int	xyz_correct(char *str)
{
	size_t	i;

	i = 0;
	if (matrix_correct(str))
		return (1);
	while (str[i])
	{
		if (i == 0 || str[i] == ',')
		{
			if (str[i] == ',')
				i++;
			if (check_num(str, &i))
				return (str[i]);
		}
		i++;
	}
	return (0);
}

int	check_xyz_axis(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (-1.0 > ft_atof(matrix[i]) || ft_atof(matrix[i]) > 1.0)
			return (1);
		i++;
	}
	return (0);
}

int	xyz_vectors_correct(char *str)
{
	char	**matrix;
	size_t	i;

	i = 0;
	if (matrix_correct(str))
		return (1);
	while (str[i])
	{
		if (i == 0 || str[i] == ',')
		{
			if (str[i] == ',')
				i++;
			if (check_num_beta(str, &i))
				return (1);
		}
		i++;
	}
	matrix = ft_split(str, ',');
	if (check_xyz_axis(matrix))
		return (free_double(matrix), 1);
	free_double(matrix);
	return (0);
}

int	fov_range(char *str)
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
	if (num > 180.0f)
		return (1);
	return (0);
}
