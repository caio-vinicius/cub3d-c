/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/07/27 12:00:57 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tex	init_textures(t_vars vars, t_cub *cub, t_sprite *s, t_game game)
{
	int		w;
	int		h;
	t_tex	t;

	t.no.img = mlx_xpm_file_to_image(vars.init, cub->t_no, &w, &h);
	t.so.img = mlx_xpm_file_to_image(vars.init, cub->t_so, &w, &h);
	t.we.img = mlx_xpm_file_to_image(vars.init, cub->t_we, &w, &h);
	t.ea.img = mlx_xpm_file_to_image(vars.init, cub->t_ea, &w, &h);
	s->texture.img = mlx_xpm_file_to_image(vars.init, cub->t_s, &w, &h);
	if (!t.no.img || !t.so.img || !t.we.img || !t.ea.img || !s->texture.img)
		game_print_exit(EPATH, 2, game);
	t.no.img_addr = mlx_get_data_addr(t.no.img, &t.no.bpp, &t.no.line_length,
			&t.no.endian);
	t.so.img_addr = mlx_get_data_addr(t.so.img, &t.so.bpp, &t.so.line_length,
			&t.so.endian);
	t.we.img_addr = mlx_get_data_addr(t.we.img, &t.we.bpp, &t.we.line_length,
			&t.we.endian);
	t.ea.img_addr = mlx_get_data_addr(t.ea.img, &t.ea.bpp, &t.ea.line_length,
			&t.ea.endian);
	s->texture.img_addr = (int*)mlx_get_data_addr(s->texture.img,
			&s->texture.bpp, &s->texture.line_length, &s->texture.endian);
	return (t);
}

static t_game	setup(t_game game)
{
	game.player.x = game.cub->gen.x_player * TILE_SIZE;
	game.player.y = game.cub->gen.y_player * TILE_SIZE;
	game.player.ad_direction = 0;
	game.player.ws_direction = 0;
	game.player.rot_angle = define_dir(game.cub->gen.rot_angle);
	game.player.ad_speed = 5 * (PI / 180);
	game.player.ws_speed = 5;
	game.player.fov = (60 * (PI / 180));
	game.cub->gen.window_width = game.cub->gen.cols * TILE_SIZE;
	game.cub->gen.window_height = game.cub->gen.rows * TILE_SIZE;
	define_dir_plane(game.cub->gen.rot_angle, &game.sprite);
	game.sprite.zbuffer = malloc(game.cub->width * sizeof(float));
	game.sprite.amount = game.cub->gen.amount_sprites;
	game.sprite.positions = game.cub->gen.sprites;
	game.sprite.order = ft_calloc(game.sprite.amount, sizeof(int) + 2);
	game.sprite.distance = ft_calloc(game.sprite.amount, sizeof(int) + 2);
	game.ray = malloc(game.cub->width * sizeof(t_ray));
	game.textures = init_textures(game.vars, game.cub, &game.sprite, game);
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
	return (0);
}

int				main(int argc, char *argv[])
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	game_validateargs(argc, argv, &game);
	game.vars.init = mlx_init();
	game.cub = cub_analyzecub(argv[1]);
	game_validatescreen(game.vars, game.cub);
	if (game.bmp != 1)
		game.vars.window = mlx_new_window(game.vars.init, game.cub->width,
				game.cub->height, "cub3d");
	game = setup(game);
	game_loop(0, &game);
	mlx_hook(game.vars.window, EFOCUSIN, 1L << 21, game_call_loop, &game);
	mlx_hook(game.vars.window, EKEYPRESS, 1L << 0, game_loop, &game);
	mlx_hook(game.vars.window, EKEYRELEASE, 1L << 1, release_button, &game);
	mlx_hook(game.vars.window, EKEYDESTROY, 1L << 17, game_x_exit, &game);
	mlx_loop(game.vars.init);
	return (0);
}
