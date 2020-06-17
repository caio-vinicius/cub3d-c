/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/06/17 09:28:19 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_screen_size(int argc, t_all *all)
{
	int width;
	int height;

	(void)argc;
	mlx_get_screen_size(all->vars.init, &width, &height);
	if (all->cub.width > width)
	{
		ft_putstr_fd("Warning:\nScreen width excced your current screen, \
resized to maximum.\n", 2);
		all->cub.width = width;
	}
	if (all->cub.height > height)
	{
		ft_putstr_fd("Warning:\nScreen height excced your current screen, \
resized to maximum.\n", 2);
		all->cub.height = height;
	}
}

t_all	setup(t_all all)
{
	float rot_angle;

	if (all.cub.gen.rot_angle == 'N')
		rot_angle = NORTH;
	else if (all.cub.gen.rot_angle == 'S')
		rot_angle = SOUTH;
	else if (all.cub.gen.rot_angle == 'E')
		rot_angle = EAST;
	else if (all.cub.gen.rot_angle == 'W')
		rot_angle = WEST;
	else
		rot_angle = NORTH;
	all.player.x = all.cub.gen.x_player * TILE_SIZE;
	all.player.y = all.cub.gen.y_player * TILE_SIZE;
	all.player.ad_direction = 0;
	all.player.ws_direction = 0;
	all.player.rot_angle = rot_angle;
	all.player.ad_speed = 5 * (PI / 180);
	all.player.ws_speed = 15;
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
		print_exit(EMISCUB, 2);
	all.cub = cub_analyzecub(argv[1]);
	validate_screen_size(argc, &all);
	all.vars.window = mlx_new_window(all.vars.init, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3d");
	all = setup(all);
	game_loop(0, &all);
	if (all.vars.init && all.vars.window)
	{
		mlx_hook(all.vars.window, E_KEYPRESS, M_KEYPRESS, game_loop, &all);
		mlx_hook(all.vars.window, E_KEYRELEASE, M_KEYRELEASE, release_button, &all);
		mlx_loop(all.vars.init);
	}
	return (0);
}
