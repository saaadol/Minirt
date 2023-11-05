/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:10:22 by markik            #+#    #+#             */
/*   Updated: 2023/11/03 13:12:53 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	error_print(int num)
{
	if (num == 99)
		printf("File Type is not supported\n");
	else if (num == 1)
		printf("Error\nA input misconfigured\n");
	else if (num == 2)
		printf("Error\nC input misconfigured\n");
	else if (num == 3)
		printf("Error\nL input misconfigured\n");
	else if (num == 4)
		printf("Error\nsp input misconfigured\n");
	else if (num == 5)
		printf("Error\npl input misconfigured\n");
	else if (num == 6)
		printf("Error\ncy input misconfigured\n");
	else if (num == 7)
		printf("Error\nType of element input incorrect\n");
	else if (num == 8)
		printf("Error\nA anc C and L are Essential\n");
}

t_obj	*parse(int ac, char **av)
{
	t_obj	*data;
	int		error_num;

	if (ac != 2)
		return (exit(1), NULL);
	data = malloc(sizeof(t_obj));
	error_num = parssing(av[1], data);
	if (error_num || !data)
		return (error_print(error_num), free(data), exit(1), NULL);
	return (data);
}

int	main(int ac, char **av)
{
	t_obj	*data;

	data = parse(ac, av);
	exec_part(data);
}
