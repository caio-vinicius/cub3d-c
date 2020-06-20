/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_drawsquare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:25:51 by caio              #+#    #+#             */
/*   Updated: 2020/06/20 12:25:08 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_drawsquare(t_data *data, int size, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x <= size)
	{
		game_mlxpixelput(data, x, y, color);
		if (y++ == size)
		{
			y = 0;
			x++;
		}
	}
}
