/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/06/13 17:07:02 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

t_all	setup(t_all all)
{
	all.player.x = WINDOW_WIDTH / 2;
	all.player.y = WINDOW_HEIGHT / 2;
	all.player.ad_direction = 0;
	all.player.ws_direction = 0;
	all.player.rot_angle = PI / 2;
	all.player.ad_speed = 5 * (PI / 180);
	all.player.ws_speed = 15;
	return (all);
}

int	release_button(int keycode, t_all *all)
{
	if (keycode == UP_ARROW)
		all->player.ws_direction = 0;
	else if (keycode == DOWN_ARROW)
		all->player.ws_direction = 0;
	else if (keycode == LEFT_ARROW)
		all->player.ad_direction = 0;
	else if (keycode == RIGHT_ARROW)
		all->player.ad_direction = 0;
	game_loop(0, all);
	return (0);
}

int	main(void)
{
	t_all all;

	//teste, aroque.
	all.vars.init = mlx_init();
	all.vars.window = mlx_new_window(all.vars.init, WINDOW_WIDTH, WINDOW_HEIGHT,
		"cub3d");
	all = setup(all);
	game_loop(0, &all);
	if (all.vars.init && all.vars.window)
	{
		//mlx_key_hook(all.vars.window, game_loop, &all);
		mlx_hook(all.vars.window, 2, 1L << 0, game_loop, &all);
		mlx_hook(all.vars.window, 3, 1L << 1, release_button, &all);
		//mlx_loop_hook(all.vars.init, game_loop, &all);
		mlx_loop(all.vars.init);
	}
	return (0);
}
