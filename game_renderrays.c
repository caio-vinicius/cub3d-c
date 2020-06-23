/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderrays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:33:14 by caio              #+#    #+#             */
/*   Updated: 2020/06/23 11:54:56 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_renderrays(t_data *data, t_cub *cub, t_player player, t_ray *ray)
{
	unsigned int i;

	i = 0;
	while (i < cub->width)
	{
		game_drawline(
			MINIMAP_SCALE * player.x + MINIMAP_MARGIN,
			MINIMAP_SCALE * player.y + MINIMAP_MARGIN,
			MINIMAP_SCALE * ray[i].wall_hit_x + MINIMAP_MARGIN,
			MINIMAP_SCALE * ray[i].wall_hit_y + MINIMAP_MARGIN,
			data
		);
		i++;
	}
}
