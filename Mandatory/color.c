/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:06:31 by markik            #+#    #+#             */
/*   Updated: 2023/11/03 15:07:54 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int	clamp(int c)
{
	if (c > 255)
		c = 255;
	if (c < 0)
		c = 0;
	return (c);
}

int	set_color(int R, int G, int B)
{
	int		color;
	void	*locate;

	color = 0;
	locate = &color;
	ft_memset(locate, clamp(B), 1);
	locate++;
	ft_memset(locate, clamp(G), 1);
	locate++;
	ft_memset(locate, clamp(R), 1);
	return (color);
}
