/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderwalls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:46:16 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 20:17:33 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	*choose_texture(t_tex textures, t_ray *ray, int i)
{
	unsigned int *texture;

	texture = 0;
	if (ray[i].facing_up && (!(ray[i].was_hit_vertical)))
		texture = (unsigned int*)textures.no.img_addr;
	else if (ray[i].facing_down && (!(ray[i].was_hit_vertical)))
		texture = (unsigned int*)textures.so.img_addr;
	else if (ray[i].facing_left && ray[i].was_hit_vertical)
		texture = (unsigned int*)textures.we.img_addr;
	else if (ray[i].facing_right && ray[i].was_hit_vertical)
		texture = (unsigned int*)textures.ea.img_addr;
	return (texture);
}

static int			get_offset_x(t_ray *ray, int i)
{
	int offset;

	offset = 0;
	if (ray[i].was_hit_vertical)
		offset = (int)ray[i].wall_hit_y % TILE_SIZE;
	else
		offset = (int)ray[i].wall_hit_x % TILE_SIZE;
	return (offset);
}

static void			draw_strip(t_game *game, t_wall wall, int i)
{
	int				x;
	int				y;
	unsigned int	color;
	unsigned int	*texture;

	x = 0 + (WALL_STRIP_WIDTH * i);
	y = wall.top_pixel;
	texture = choose_texture(game->textures, game->ray, i);
	wall.texture_offset_x = get_offset_x(game->ray, i);
	while (y < wall.bottom_pixel)
	{
		wall.distance_from_top = y + (wall.strip_height / 2) -
			(game->cub->height / 2);
		wall.texture_offset_y = wall.distance_from_top * ((float)TEX_HEIGHT /
				wall.strip_height);
		color = texture[(TEX_WIDTH * wall.texture_offset_y) +
			wall.texture_offset_x];
		game_mlxpixelput(&game->data, x, y, color);
		x++;
		if (x == WALL_STRIP_WIDTH + (WALL_STRIP_WIDTH * i))
		{
			x = 0 + (WALL_STRIP_WIDTH * i);
			y++;
		}
	}
}

void				game_renderwalls(t_game *game)
{
	unsigned int	i;
	t_wall			wall;

	i = 0;
	while (i < game->cub->width)
	{
		wall.perp_distance = game->ray[i].distance * cos(game->ray[i].angle -
				game->player.rot_angle);
		game->sprite.zbuffer[i] = wall.perp_distance / TILE_SIZE;
		wall.distance_projection_plane = (game->cub->width / 2) /
			tan(game->player.fov / 2);
		wall.strip_height = (TILE_SIZE / wall.perp_distance) *
			wall.distance_projection_plane;
		wall.top_pixel = (game->cub->height / 2) - (wall.strip_height / 2);
		wall.top_pixel = (wall.top_pixel < 0) ? 0 : wall.top_pixel;
		wall.bottom_pixel = (game->cub->height / 2) + (wall.strip_height / 2);
		wall.bottom_pixel = (wall.bottom_pixel > (int)game->cub->height) ?
			game->cub->height : wall.bottom_pixel;
		draw_strip(game, wall, i);
		i++;
	}
}
