#include "Minirt.h"

static	int	isspace3(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 9 && (str[i] <= 13 || str[i] == 32))
			i++;
		else
			break ;
	}
	return (i);
}

int	ft_atoi(char *str)
{
	long	res;
	int		signe;
	int		i;

	i = isspace3(str);
	res = 0;
	signe = 1;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			signe = signe * (-1);
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * signe);
}