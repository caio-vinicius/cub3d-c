/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderwalls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:46:16 by caio              #+#    #+#             */
/*   Updated: 2020/06/20 12:58:09 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_strip(t_data *data, t_wall wall, int color, int i)
{
	int x;
	int y;

	x = 0 + (WALL_STRIP_WIDTH * i);
	y = wall.top_pixel;
	//printf("x %d y %x\n", x, y);
	while (y < wall.bottom_pixel)
	{
		game_mlxpixelput(data, x, y, color);
		x++;
		if (x == WALL_STRIP_WIDTH + (WALL_STRIP_WIDTH * i))
		{
			x = 0 + (WALL_STRIP_WIDTH * i);
			y++;
		}
	}
}

//check this
void	game_renderwalls(t_data *data, t_ray *ray, t_cub *cub, t_player player)
{
	unsigned int i;
	int color;
	t_wall wall;

	i = 0;
	while (i < cub->width)
	{
		wall.perp_distance = ray[i].distance * cos(ray[i].angle - player.rot_angle);
		wall.distance_projection_plane = (cub->width / 2) / tan(FOV_ANGLE / 2);
		wall.projected_height = (TILE_SIZE / wall.perp_distance) * wall.distance_projection_plane;
		wall.strip_height = wall.projected_height;
		wall.top_pixel = (cub->height / 2) - (wall.strip_height / 2);
		wall.top_pixel = (wall.top_pixel < 0) ? 0 : wall.top_pixel;
		wall.bottom_pixel = (cub->height / 2) + (wall.strip_height / 2);
		wall.bottom_pixel = (wall.bottom_pixel > (int)cub->height) ? cub->height : wall.bottom_pixel;
		color = (ray[i].was_hit_vertical) ? WALL_3D_COLOR : WALL_3D_2COLOR;
		draw_strip(data, wall, color, i);
		i++;
	}
}
