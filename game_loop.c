/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:37:17 by caio              #+#    #+#             */
/*   Updated: 2020/06/19 15:23:04 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_all all)
{
	all.data.img = mlx_new_image(all.vars.init, all.cub->width, all.cub->height);
	all.data.img_addr = mlx_get_data_addr(all.data.img, &all.data.bpp,
			&all.data.line_length, &all.data.endian);

	render_background(&all.data, *all.cub);
	render_walls(&all.data, all);
	render_map(&all.data, *all.cub);
	//render_player(all);

	mlx_put_image_to_window(all.vars.init, all.vars.window, all.data.img, 0, 0);
	mlx_destroy_image(all.vars.init, all.data.img);

	render_rays(&all);
}

void	update(t_all *all)
{
	move_player(&all->player, *all->cub);
	cast_all_rays(all);
}

void	process_keys(int keycode, t_all *all)
{
	if (keycode == UP_ARROW)
		all->player.ws_direction = 1;
	else if (keycode == DOWN_ARROW)
		all->player.ws_direction = -1;
	else if (keycode == LEFT_ARROW)
		all->player.ad_direction = -1;
	else if (keycode == RIGHT_ARROW)
		all->player.ad_direction = 1;
	else if (keycode == ESC)
		game_print_exit(CLOSECL, 1, *all);
}

int	game_loop(int keycode, t_all *all)
{
	process_keys(keycode, all);
	update(all);
	render(*all);
	return (0);
}
