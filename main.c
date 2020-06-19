/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/06/19 15:16:38 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_screen_size(int argc, t_all *all)
{
	int width;
	int height;

	(void)argc;
	mlx_get_screen_size(all->vars.init, &width, &height);
	if (all->cub->width > (unsigned int)width)
		all->cub->width = width;
	if (all->cub->height > (unsigned int)height)
		all->cub->height = height;
}

float	define_dir(char rot_angle)
{
	float dir;

	if (rot_angle == 'N')
		dir = NORTH;
	else if (rot_angle == 'S')
		dir = SOUTH;
	else if (rot_angle == 'E')
		dir = EAST;
	else if (rot_angle == 'W')
		dir = WEST;
	else
		dir = NORTH;
	return (rot_angle);
}

t_all	setup(t_all all)
{
	all.player.x = all.cub->gen.x_player * TILE_SIZE;
	all.player.y = all.cub->gen.y_player * TILE_SIZE;
	all.player.ad_direction = 0;
	all.player.ws_direction = 0;
	all.player.rot_angle = define_dir(all.cub->gen.rot_angle);
	all.player.ad_speed = 5 * (PI / 180);
	all.player.ws_speed = 15;
	all.cub->gen.window_width = all.cub->gen.cols * TILE_SIZE;
	all.cub->gen.window_height = all.cub->gen.rows * TILE_SIZE;
	all.ray = malloc(all.cub->width * sizeof(t_ray));
	return (all);
}

int		release_button(int keycode, t_all *all)
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

int		main(int argc, char *argv[])
{
	t_all	all;

	all.vars.init = mlx_init();
	if (!argv[1])
		game_print_exit(EMISCUB, 2, all);
	all.cub = cub_analyzecub(argv[1]);
	validate_screen_size(argc, &all);
	all.vars.window = mlx_new_window(all.vars.init, all.cub->width,
			all.cub->height, "cub3d");
	all = setup(all);
	game_loop(0, &all);

	mlx_hook(all.vars.window, E_KEYPRESS, M_KEYPRESS, game_loop, &all);
	mlx_hook(all.vars.window, E_KEYRELEASE, M_KEYRELEASE, release_button, &all);
	mlx_loop(all.vars.init);
	return (0);
}
