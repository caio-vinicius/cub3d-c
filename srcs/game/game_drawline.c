/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_drawline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:34:31 by caio              #+#    #+#             */
/*   Updated: 2020/07/20 20:39:00 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	sabs(int n)
{
	return ((n > 0) ? n : (n * (-1)));
}

void		game_drawline(int x0, int y0, int x1, int y1, t_data *data)
{
	int		steps;
	float	x;
	float	y;
	int		i;

	i = 0;
	steps = sabs(x1 - x0) > sabs(y1 - y0) ? sabs(x1 - x0) : sabs(y1 - y0);
	x = x0;
	y = y0;
	while (i <= steps)
	{
		game_mlxpixelput(data, round(x), round(y), 0x0000ff);
		x += (x1 - x0) / (float)steps;
		y += (y1 - y0) / (float)steps;
		i++;
	}
}
