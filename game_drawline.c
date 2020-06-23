/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_drawline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:34:31 by caio              #+#    #+#             */
/*   Updated: 2020/06/23 11:50:02 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int abs(int n)
{
	return ((n>0) ? n : ( n * (-1)));
}

void game_drawline(int x0, int y0, int x1, int y1, t_data *data)
{
	int dx;
	int dy;
	int steps;
	float x_increase;
	float y_increase;
	float x;
	float y;
	int i;

	i = 0;
	dx = x1 - x0;
	dy = y1 - y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x_increase = dx / (float)steps;
	y_increase = dy / (float)steps;
	x = x0;
	y = y0;
	while (i <= steps)
	{
		game_mlxpixelput(data, round(x), round(y), 0x0000ff);
		x += x_increase;
		y += y_increase;
		i++;
	}
}
