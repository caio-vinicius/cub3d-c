/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:37:17 by caio              #+#    #+#             */
/*   Updated: 2020/06/05 21:18:22 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_all all)
{
	t_data data;
	data.img = mlx_new_image(all.vars.init, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img_addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
		&data.endian);

	render_background(all, &data);
	render_walls(all.ray, all.player, &data, all);
	render_map(all.vars, &data);
	//render_player(all);
	
	mlx_put_image_to_window(all.vars.init, all.vars.window, data.img, 0, 0);
	mlx_destroy_image(all.vars.init, data.img);	

	render_rays(&all);
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
