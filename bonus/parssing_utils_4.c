/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:32:08 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 14:37:08 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int	matrix_correct(char *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == ',')
			size++;
		i++;
	}
	if (size != 2)
		return (1);
	return (0);
}

int	check_rgb(char *str)
{
	size_t	i;
	int		num;

	i = 0;
	num = 0;
	if (matrix_correct(str))
		return (1);
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (num > 255)
				return (1);
			num = 0;
		}
		else if (48 <= str[i] && str[i] <= 57)
			num = (num * 10) + (str[i] - 48);
		else if (str[i] != 32 && str[i] != 9 && str[i] != 10 \
				&& str[i] != 11 && str[i] != 12 && str[i] != 13)
			return (1);
		i++; 
	}
	if (num > 255)
		return (1);
	return (0);
}

int	ambient_lightning_protection(char *line)
{
	char	**splite;
	size_t	i;

	i = 0;
	splite = ft_split(line, ' ');
	if (splite_size(splite) != 3)
		return (free_double(splite), 1);
	if (ft_strncmp(splite[0], "A", 2))
		return (free_double(splite), 1);
	if (0.0f > ft_atof(splite[1]) || ft_atof(splite[1]) > 1.0f)
		return (free_double(splite), 1);
	if (check_rgb(splite[2]))
		return (free_double(splite), 1);
	return (free_double(splite), 0);
}

int	check_num(char *str, size_t *i)
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
