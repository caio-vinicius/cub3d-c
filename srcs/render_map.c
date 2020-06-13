/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:27:44 by caio              #+#    #+#             */
/*   Updated: 2020/06/13 17:09:33 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_on_image(t_data *data, int x1, int y1, int size)
{
	int x;
	int y;

	x = 0 + x1 * size;
	y = 0 + y1 * size;
	while (y < size + (y1 * size))
	{
		my_mlx_pixel_put(data, x, y, WALL_2D_COLOR);
		x++;
		if (x == size + (x1 * size))
		{
			x = 0 + (x1 * size);
			y++;
		}
	}
}

void	render_map(t_data *data)
{
	int	size;
	int	x;
	int	y;

	x = 0;
	y = 0;
	size = TILE_SIZE * MINIMAP_SCALE;
	while (x < MAP_NUM_ROWS)
	{
		while (y < MAP_NUM_COLS)
		{
			if (map[x][y] == 1)
				draw_wall_on_image(data, y, x, size);
			y++;
		}
		y = 0;
		x++;
	}
}
