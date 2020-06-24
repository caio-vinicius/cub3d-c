/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderwalls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:46:16 by caio              #+#    #+#             */
/*   Updated: 2020/06/24 17:55:32 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_strip(t_data *data, t_ray *ray, t_wall wall, int i,
		unsigned int *texture)
{
	int x;
	int y;
	unsigned int pixel_texture;

	x = 0 + (WALL_STRIP_WIDTH * i);
	y = wall.top_pixel;
	if (ray[i].was_hit_vertical)
		wall.texture_offset_x = (int)ray[i].wall_hit_y % TILE_SIZE;
	else
		wall.texture_offset_x = (int)ray[i].wall_hit_x % TILE_SIZE;
	while (y < wall.bottom_pixel)
	{
		wall.distance_from_top = y + (wall.strip_height / 2) - (500 / 2);
		wall.texture_offset_y = wall.distance_from_top * ((float)TEX_HEIGHT / wall.strip_height);
		pixel_texture = texture[(TEX_WIDTH * wall.texture_offset_y) + wall.texture_offset_x];
		game_mlxpixelput(data, x, y, pixel_texture);
		x++;
		if (x == WALL_STRIP_WIDTH + (WALL_STRIP_WIDTH * i))
		{
			x = 0 + (WALL_STRIP_WIDTH * i);
			y++;
		}
	}
}

static unsigned int		*draw_texture()
{
	unsigned int *wall_texture;
	int x;
	int y;

	x = 0;
	y = 0;
	wall_texture = malloc(TEX_WIDTH * TEX_HEIGHT * 4);
	while (x < TEX_WIDTH)
	{
		while (y < TEX_HEIGHT)
		{
			wall_texture[(TEX_WIDTH * y) + x] = (x % 8 && y % 8) ? 0x000000 :
				0xffffff;
			y++;
		}
		y = 0;
		x++;
	}
	return (wall_texture);
}

//check this
void	game_renderwalls(t_data *data, t_ray *ray, t_cub *cub, t_player player)
{
	unsigned int pixel_texture;
	unsigned int *wall_texture;
	unsigned int i;
	t_wall wall;

	i = 0;
	wall_texture = draw_texture();
	pixel_texture = 0;
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
		draw_strip(data, ray, wall, i, wall_texture);
		i++;
	}
}
