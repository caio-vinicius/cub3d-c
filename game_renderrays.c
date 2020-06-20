/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderrays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:33:14 by caio              #+#    #+#             */
/*   Updated: 2020/06/20 13:19:10 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_renderrays(t_cub *cub, t_player player, t_ray *ray, t_vars vars)
{
	unsigned int i;

	i = 0;
	while (i < cub->width)
	{
		game_drawline(
			MINIMAP_SCALE * player.x,
			MINIMAP_SCALE * player.y,
			MINIMAP_SCALE * ray[i].wall_hit_x,
			MINIMAP_SCALE * ray[i].wall_hit_y,
			vars
		);
		i++;
	}
}
