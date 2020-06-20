/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/06/20 13:15:20 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_screen_size(int argc, t_vars vars, t_cub *cub)
{
	int width;
	int height;

	(void)argc;
	mlx_get_screen_size(vars.init, &width, &height);
	if (cub->width > (unsigned int)width)
		cub->width = width;
	if (cub->height > (unsigned int)height)
		cub->height = height;
}

static float	define_dir(char rot_angle)
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

static t_game	setup(t_game game)
{
	game.player.x = game.cub->gen.x_player * TILE_SIZE;
	game.player.y = game.cub->gen.y_player * TILE_SIZE;
	game.player.ad_direction = 0;
	game.player.ws_direction = 0;
	game.player.rot_angle = define_dir(game.cub->gen.rot_angle);
	game.player.ad_speed = 5 * (PI / 180);
	game.player.ws_speed = 15;
	game.cub->gen.window_width = game.cub->gen.cols * TILE_SIZE;
	game.cub->gen.window_height = game.cub->gen.rows * TILE_SIZE;
	game.ray = malloc(game.cub->width * sizeof(t_ray));
	return (game);
}

static int		release_button(int keycode, t_game *game)
{
	if (keycode == UP_ARROW)
		game->player.ws_direction = 0;
	else if (keycode == DOWN_ARROW)
		game->player.ws_direction = 0;
	else if (keycode == LEFT_ARROW)
		game->player.ad_direction = 0;
	else if (keycode == RIGHT_ARROW)
		game->player.ad_direction = 0;
	game_loop(0, game);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_game	game;

	game.vars.init = mlx_init();
	if (!argv[1])
		game_print_exit(EMISCUB, 2, game);
	game.cub = cub_analyzecub(argv[1]);
	validate_screen_size(argc, game.vars, game.cub);
	game.vars.window = mlx_new_window(game.vars.init, game.cub->width,
			game.cub->height, "cub3d");
	game = setup(game);
	game_loop(0, &game);

	mlx_hook(game.vars.window, E_KEYPRESS, M_KEYPRESS, game_loop, &game);
	mlx_hook(game.vars.window, E_KEYRELEASE, M_KEYRELEASE, release_button, &game);
	mlx_loop(game.vars.init);
	return (0);
}
