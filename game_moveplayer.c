/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_moveplayer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:32:03 by caio              #+#    #+#             */
/*   Updated: 2020/07/12 12:01:23 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_moveplayer(t_player *player, t_cub cub, t_sprite *sprite)
{
	float move_step;
	float new_x;
	float new_y;

	//sprite variables start
	float old_dir_x;
	float old_plane_x;
	float dir_angle;

	old_dir_x = sprite->dir_x;
	old_plane_x = sprite->plane_x;
	dir_angle = player->ad_direction * player->ad_speed;
	//sprite variables end

	//rotation
	player->rot_angle += player->ad_direction * player->ad_speed;
	//walk
	move_step = player->ws_direction * player->ws_speed;
	new_x = player->x + cos(player->rot_angle) * move_step;
	new_y = player->y + sin(player->rot_angle) * move_step;
	new_x = ceil(new_x);
	new_y = ceil(new_y);

	//sprite
	sprite->dir_x = sprite->dir_x * cos(dir_angle) - sprite->dir_y * sin(dir_angle);
	sprite->dir_y = old_dir_x * sin(dir_angle) + sprite->dir_y * cos(dir_angle);
	sprite->plane_x = sprite->plane_x * cos(dir_angle) - sprite->plane_y * sin(dir_angle);
	sprite->plane_y = old_plane_x * sin(dir_angle) + sprite->plane_y * cos(dir_angle);

	if (game_iswalkable(new_x, new_y, cub.map, cub.gen))
	{
		player->x = new_x;
		player->y = new_y;
	}
}
