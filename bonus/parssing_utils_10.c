/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils_10.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:30:09 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 19:18:34 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	ft_matrix(char *str, double *x, double *y, double *z)
{
	char	**matrix;

	matrix = ft_split(str, ',');
	*x = ft_atof(matrix[0]);
	*y = ft_atof(matrix[1]);
	*z = ft_atof(matrix[2]);
	free_double(matrix);
}

int	protections(char **lines)
{
	size_t	i;
	int		error;
	int		flag_a;
	int		flag_c;
	int		flag_l;

	i = 0;
	flag_a = 0;
	flag_c = 0;
	flag_l = 0;
	while (lines[i])
	{
		error = protection_tool(lines[i], &flag_a, &flag_c, &flag_l);
		if (error)
			return (error);
		i++;
	}
	return (0);
}

int	splite_size(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i][0] == '\n')
			j++;
		i++;
	}
	return (i - j);
}
