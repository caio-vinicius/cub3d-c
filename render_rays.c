/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:33:14 by caio              #+#    #+#             */
/*   Updated: 2020/05/29 13:34:08 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_rays(t_all *all)
{
	int i;

	i = 0;
	while (i < NUM_RAYS)
	{
		dda_draw_line(MINIMAP_SCALE * all->player.x,
			MINIMAP_SCALE * all->player.y,
			MINIMAP_SCALE * all->ray[i].wall_hit_x,
			MINIMAP_SCALE * all->ray[i].wall_hit_y, all->vars);
		i++;
	}
}
