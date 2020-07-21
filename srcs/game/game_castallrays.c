/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_castallrays.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:34:30 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 20:17:13 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_castallrays(t_game *game)
{
	float			ray_angle;
	unsigned int	id;

	id = 0;
	ray_angle = game->player.rot_angle - (game->player.fov / 2);
	while (id < game->cub->width)
	{
		game_castray(ray_angle, id, game);
		ray_angle += game->player.fov / game->cub->width;
		id++;
	}
}
