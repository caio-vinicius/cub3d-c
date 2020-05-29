/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:27:44 by caio              #+#    #+#             */
/*   Updated: 2020/05/29 13:28:06 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(int x, int y, t_vars vars)
{
	t_data	data;
	int	size;

	size = TILE_SIZE * MINIMAP_SCALE;
	data.img = mlx_new_image(vars.init, size, size);
	data.img_addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
		&data.endian);
	draw_square_on_image(&data, size, 0xffffff);
	mlx_put_image_to_window(vars.init, vars.window, data.img, x, y);
	mlx_destroy_image(vars.init, data.img);
}

void	render_map(t_vars vars)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < MAP_NUM_ROWS)
	{
		while (y < MAP_NUM_COLS)
		{
			if (map[x][y] == 1)
				draw_wall((y * TILE_SIZE) * MINIMAP_SCALE,
					(x * TILE_SIZE) * MINIMAP_SCALE, vars);
			y++;
		}
		y = 0;
		x++;
	}
}
