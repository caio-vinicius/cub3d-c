/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rendermap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:27:44 by caio              #+#    #+#             */
/*   Updated: 2020/07/20 14:49:32 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_on_image(t_data *data, int x1, int y1, int size)
{
	int x;
	int y;

	x = 0 + x1 * size;
	y = 0 + y1 * size;
	while (y < size + (y1 * size))
	{
		game_mlxpixelput(data, x + MINIMAP_MARGIN, y + MINIMAP_MARGIN,
				WALL_2D_COLOR);
		x++;
		if (x == size + (x1 * size))
		{
			x = 0 + (x1 * size);
			y++;
		}
	}
}

void		game_rendermap(t_data *data, t_cub *cub)
{
	int	size;
	int	x;
	int	y;

	x = 0;
	y = 0;
	size = TILE_SIZE * MINIMAP_SCALE;
	while (x < cub->gen.rows)
	{
		while (y < cub->gen.cols)
		{
			if (cub->map[x][y] == '1')
				draw_wall_on_image(data, y, x, size);
			y++;
		}
		y = 0;
		x++;
	}
}
