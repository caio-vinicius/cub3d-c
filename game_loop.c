/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:37:17 by caio              #+#    #+#             */
/*   Updated: 2020/05/29 13:38:25 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_all all)
{
	render_player(all);
	render_rays(&all);
	render_map(all.vars);
}

void	update(t_all *all)
{
	move_player(&all->player);
	cast_all_rays(all);
}

void	process_keys(int keycode, t_player *player)
{
	if (keycode == UP_ARROW)
		player->ws_direction = 1;
	else if (keycode == DOWN_ARROW)
		player->ws_direction = -1;
	else if (keycode == LEFT_ARROW)
		player->ad_direction = -1;
	else if (keycode == RIGHT_ARROW)
		player->ad_direction = 1;
}

int	game_loop(int keycode, t_all *all)
{
	process_keys(keycode, &all->player);
	update(all);
	render(*all);
}
