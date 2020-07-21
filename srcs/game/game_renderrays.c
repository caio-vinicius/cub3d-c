/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderrays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:33:14 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 17:33:13 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_renderrays(t_data *data, t_cub *cub, t_player player, t_ray *ray)
{
	unsigned int	i;
	t_draw_line		vars;

	i = 0;
	while (i < cub->width)
	{
		vars.x0 = MINIMAP_SCALE * player.x + MINIMAP_MARGIN;
		vars.y0 = MINIMAP_SCALE * player.y + MINIMAP_MARGIN;
		vars.x1 = MINIMAP_SCALE * ray[i].wall_hit_x + MINIMAP_MARGIN;
		vars.y1 = MINIMAP_SCALE * ray[i].wall_hit_y + MINIMAP_MARGIN;
		game_drawline(vars, data);
		i++;
	}
}
