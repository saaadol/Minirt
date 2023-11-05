/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:20:16 by souledla          #+#    #+#             */
/*   Updated: 2023/11/05 15:31:41 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	free_double_(t_obj *data, int status)
{
	int	i;

	i = 0;
	if (status == 2)
	{
		while (data->cy[i])
			free(data->cy[i++]);
		free(data->cy);
	}
	else if (status == 3)
	{
		while (data->pl[i])
			free(data->pl[i++]);
		free(data->pl);
	}
	else if (status == 4)
	{
		while (data->sp[i])
			free(data->sp[i++]);
		free(data->sp);
	}
	return ;
}

void	free_struct(t_obj *data)
{
	int	i;

	i = 0;
	if (data->a)
		free(data->a);
	if (data->c)
		free(data->c);
	if (data->l)
	{
		while (data->l[i])
			free(data->l[i++]);
		free(data->l);
	}
	if (data->cn)
		free(data->cn);
	if (data->cy)
		free_double_(data, 2);
	if (data->pl)
		free_double_(data, 3);
	if (data->sp)
		free_double_(data, 4);
	return ;
}
