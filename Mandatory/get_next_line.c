/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 01:01:16 by markik            #+#    #+#             */
/*   Updated: 2023/10/04 20:23:42 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	if (s[i] == (char)c)
		return (1);
	return (0);
}

char	*ft_reading_to_stock(int fd, char *stock)
{
	char	*str;
	int		count;

	count = 1;
	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (free(stock), NULL);
	while (ft_strchr(stock, '\n') == 0 && count != 0)
	{
		count = read(fd, str, BUFFER_SIZE);
		if (count == -1)
			return (free(str), free(stock), NULL);
		str[count] = '\0';
		if (stock == NULL)
			stock = ft_strdup(str);
		else
			stock = ft_strjoin(stock, str);
	}
	if (stock[0] == '\0')
	{
		free(stock);
		stock = NULL;
	}
	return (free(str), stock);
}

char	*ft_liner(char *stock)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (0);
	while (stock[j] && stock[j] != '\n')
	{
		str[j] = stock[j];
		j++;
	}
	if (stock[j] == '\n')
	{
		str[j] = '\n';
		str[j + 1] = '\0';
	}
	else
		str[j] = '\0';
	return (str);
}

char	*ft_stockage(char *stock)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stock)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
		return (free(stock), NULL);
	i++;
	str = malloc(sizeof(char) * (ft_strlen(stock) - i + 1));
	if (!str)
		return (0);
	while (stock[i])
	{
		str[j] = stock[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(stock);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stock = ft_reading_to_stock(fd, stock);
	if (!stock)
		return (0);
	line = ft_liner(stock);
	stock = ft_stockage(stock);
	return (line);
}
