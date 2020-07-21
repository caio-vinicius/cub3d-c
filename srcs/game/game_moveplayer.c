/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_moveplayer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:32:03 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 12:40:07 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_sprite(float x, float y, char **map)
{
	int x_map;
	int y_map;

	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if (map[y_map][x_map] == '2')
		return (0);
	return (1);
}

void		game_moveplayer(t_player *player, t_cub cub, t_sprite *s)
{
	float new_x;
	float new_y;
	float old_dir_x;
	float old_plane_x;
	float dir_angle;

	old_dir_x = s->dir_x;
	old_plane_x = s->plane_x;
	dir_angle = player->ad_direction * player->ad_speed;
	player->rot_angle += player->ad_direction * player->ad_speed;
	new_x = ceil(player->x + cos(player->rot_angle) *
			(player->ws_direction * player->ws_speed));
	new_y = ceil(player->y + sin(player->rot_angle) *
			(player->ws_direction * player->ws_speed));
	s->dir_x = s->dir_x * cos(dir_angle) - s->dir_y * sin(dir_angle);
	s->dir_y = old_dir_x * sin(dir_angle) + s->dir_y * cos(dir_angle);
	s->plane_x = s->plane_x * cos(dir_angle) - s->plane_y * sin(dir_angle);
	s->plane_y = old_plane_x * sin(dir_angle) + s->plane_y * cos(dir_angle);
	if (game_iswalkable(new_x, new_y, cub.map, cub.gen) &&
			(is_sprite(new_x, new_y, cub.map)))
	{
		player->x = new_x;
		player->y = new_y;
	}
}
