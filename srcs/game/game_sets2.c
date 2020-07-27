/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sets2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 17:34:47 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 17:38:50 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray_vars	find_coords_to_check(t_ray_vars ray, t_grid_vars *vars, int time)
{
	if (time == 0)
		ray.x_to_check = vars->next_touch_x;
	else
		ray.x_to_check = vars->next_touch_x + ((ray.facing_left) ? -1 : 0);
	if (time == 1)
		ray.y_to_check = vars->next_touch_y;
	else
		ray.y_to_check = vars->next_touch_y + ((ray.facing_up) ? -1 : 0);
	return (ray);
}

int		game_x_exit(t_game *game)
{
	game_print_exit(CLOSECL, 1, *game);
	return (0);
}

int		game_call_loop(t_game *game)
{
	game_loop(0, game);
	return (0);
}
