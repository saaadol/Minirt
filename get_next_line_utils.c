/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 01:02:52 by markik            #+#    #+#             */
/*   Updated: 2023/10/27 00:31:11 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

char	*ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char		*dest;
	size_t		src_size;

	src_size = ft_strlen(src);
	dest = malloc(sizeof (char) * (src_size + 1));
	if (dest == NULL)
		return (NULL);
	dest = ft_strcpy(dest, src);
	return (dest);
}

void	ft_strcat(char *str, char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[j])
	{
		str[i] = dest [i];
		i++;
		j++;
	}
	j = 0;
	while (src[j])
	{
		str[i] = src[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*str;

	len = ((ft_strlen(s1) + ft_strlen(s2)) + 1);
	str = (char *)malloc(sizeof (char) * len);
	if (!str)
		return (0);
	ft_strcat(str, (char *)s1, (char *)s2);
	free(s1);
	return (str);
}


static size_t	ft_checklast(char *s, char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s) - 1;
	while (set[i])
	{
		if (j > 0 && s[j] == set[i])
		{
			j--;
			i = 0;
		}
		else
			i++;
	}
	if (j < 0)
		return (0);
	return (j);
}

static size_t	ft_checkbeg(char *s, char *set)
{
	size_t	i;
	size_t	z;

	i = 0;
	z = 0;
	while (set[i])
	{
		if (s[z] == set[i])
		{
			z++;
			i = 0;
		}
		else
			i++;
	}
	return (z);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *) b;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;
	size_t	s;

	s = count * size;
	str = malloc(s);
	if (!str)
		return (NULL);
	ft_bzero(str, (count * size));
	return (str);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	size_t	end;
	size_t	start;
	char	*p;

	if (s1 == 0 || set == 0)
		return (0);
	if (s1[0] == '\0')
		return (0);
	i = 0;
	start = ft_checkbeg(s1, set);
	end = ft_checklast(s1, set);
	if (start > end)
		return (0);
	if (start > end)
		return ((char *)ft_calloc(1, 1));
	p = malloc(sizeof(char) * ((end - start) + 2));
	if (!p)
		return (0);
	while (start <= end)
		p[i++] = s1[start++];
	p[i] = '\0';
	return (p);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (count);
}

static size_t	ft_strlen_checker(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **str, size_t j)
{
	int	i;

	i = j;
	while (i >= 0)
	{
		if (i == 0)
		{
			free(str[i]);
			str[i] = 0;
			break ;
		}
		free(str[i]);
		str[i] = 0;
		i--;
	}
	free(str);
	str = 0;
	return (0);
}

static char	*ft_word(char const *s, char c)
{
	size_t	len_word;
	size_t	i;
	char	*word;

	i = 0;
	len_word = ft_strlen_checker(s, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (0);
	while (i < len_word)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	str = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!str)
		return (0);
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			str[i] = ft_word(s, c);
			if (!(str[i]))
				return (ft_free(str, i));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	str[i] = 0;
	return (str);
}
