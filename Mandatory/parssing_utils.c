/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:48:11 by markik            #+#    #+#             */
/*   Updated: 2023/11/04 13:50:28 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (str1[i] != str2[i] || str1[i] == 0 || str2[i] == 0)
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	type_check(char *file)
{
	int	len;

	if (!file)
		return (1);
	len = ft_strlen(file) - 1;
	while (len >= 0)
	{
		if (file[len] == '.')
			break ;
		len--;
	}
	if (!ft_strncmp(file + len, ".rt", 4))
		return (0);
	return (1);
}

size_t	lst_size(t_save *list)
{
	t_save	*head;
	size_t	size;

	head = list;
	size = 0;
	while (head->line)
	{
		size++;
		head = head->next;
	}
	return (size);
}
