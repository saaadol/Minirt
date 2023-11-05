/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:10:34 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 19:08:09 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

char	*new_line(char *line)
{
	char	*str;
	size_t	size;
	size_t	i;
	size_t	j;

	size = no_multi_space_size(line);
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (size + 1));
	while (line[i])
	{
		while (line[i] == 32 && line[i + 1] == 32)
			i++;
		str[j] = line[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free(line);
	return (str);
}

void	remove_multiple_space(char **file_line)
{
	size_t	i;

	i = 0;
	while (file_line[i])
	{
		if (multi_space(file_line[i]))
			file_line[i] = new_line(file_line[i]);
		i++;
	}
}

int	signe_init(char *str, int *i)
{
	int	signe;

	signe = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			signe = -1;
		(*i)++;
	}
	return (signe);
}

double	num_atof(int flag, int i, double num)
{
	int	size;

	size = (i - 1) - flag;
	while (size)
	{
		num = num / 10;
		size--;
	}
	return (num);
}

double	ft_atof(char *str)
{
	double	num;
	int		flag;
	int		signe;
	int		i;

	i = 0;
	num = 0;
	flag = 0;
	signe = signe_init(str, &i);
	while (str[i])
	{
		if (str[i] == '.' && flag == 0)
			flag = i;
		else if (48 <= str[i] && str[i] <= 57)
			num = (num * 10) + str[i] - 48;
		else if (str[i] != '\n')
			return (10.0f);
		i++;
	}
	if (flag != 0)
		num = num_atof(flag, i, num);
	return (num * signe);
}
