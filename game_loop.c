/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:37:17 by caio              #+#    #+#             */
/*   Updated: 2020/06/20 13:21:14 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render(t_game game)
{
	game.data.img = mlx_new_image(game.vars.init, game.cub->width, game.cub->height);
	game.data.img_addr = mlx_get_data_addr(game.data.img, &game.data.bpp,
			&game.data.line_length, &game.data.endian);

	game_renderbackground(&game.data, game.cub);
	game_renderwalls(&game.data, game.ray, game.cub, game.player);
	game_rendermap(&game.data, game.cub);
	//game_renderplayer(game.player, game.vars);

	mlx_put_image_to_window(game.vars.init, game.vars.window, game.data.img, 0, 0);
	mlx_destroy_image(game.vars.init, game.data.img);

	game_renderrays(game.cub, game.player, game.ray, game.vars);
}

static void	update(t_game *game)
{
	game_moveplayer(&game->player, *game->cub);
	game_castallrays(game);
}

static void	process_keys(int keycode, t_game *game)
{
	if (keycode == UP_ARROW)
		game->player.ws_direction = 1;
	else if (keycode == DOWN_ARROW)
		game->player.ws_direction = -1;
	else if (keycode == LEFT_ARROW)
		game->player.ad_direction = -1;
	else if (keycode == RIGHT_ARROW)
		game->player.ad_direction = 1;
	else if (keycode == ESC)
		game_print_exit(CLOSECL, 1, *game);
}

int	game_loop(int keycode, t_game *game)
{
	process_keys(keycode, game);
	update(game);
	render(*game);
	return (0);
}
