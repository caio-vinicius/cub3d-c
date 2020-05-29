/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:32:03 by caio              #+#    #+#             */
/*   Updated: 2020/05/29 13:34:02 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_player *player)
{
	float move_step;
	float new_x;
	float new_y;

	//rotation
	player->rot_angle += player->ad_direction * player->ad_speed;
	//walk
	move_step = player->ws_direction * player->ws_speed;
	new_x = player->x + cos(player->rot_angle) * move_step;
	new_y = player->y + sin(player->rot_angle) * move_step;
	new_x = ceil(new_x);
	new_y = ceil(new_y);
	if (is_walkable(new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}
