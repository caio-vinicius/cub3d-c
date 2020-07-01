/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/07/01 11:47:21 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (dir);
}

static t_tex	init_textures(t_vars vars, t_cub *cub)
{
	int width;
	int height;
	t_tex textures;

	textures.no.img = mlx_xpm_file_to_image(vars.init, cub->t_no,
			&width, &height);
	textures.no.img_addr = mlx_get_data_addr(textures.no.img, &textures.no.bpp,
			&textures.no.line_length, &textures.no.endian);
	textures.so.img = mlx_xpm_file_to_image(vars.init, cub->t_so,
			&width, &height);
	textures.so.img_addr = mlx_get_data_addr(textures.so.img, &textures.so.bpp,
			&textures.so.line_length, &textures.so.endian);
	textures.we.img = mlx_xpm_file_to_image(vars.init, cub->t_we,
			&width, &height);
	textures.we.img_addr = mlx_get_data_addr(textures.we.img, &textures.we.bpp,
			&textures.we.line_length, &textures.we.endian);
	textures.ea.img = mlx_xpm_file_to_image(vars.init, cub->t_ea,
			&width, &height);
	textures.ea.img_addr = mlx_get_data_addr(textures.ea.img, &textures.ea.bpp,
			&textures.ea.line_length, &textures.ea.endian);
	textures.s.img = mlx_xpm_file_to_image(vars.init, cub->t_s, &width,
			&height);
	textures.s.img_addr = mlx_get_data_addr(textures.s.img, &textures.s.bpp,
			&textures.s.line_length, &textures.s.endian);
	return (textures);
}

static	void	define_dir_plane(char pos, t_sprite *sprite, t_player player)
{
	sprite->pos_x = (float)player.x + 0.5;
	sprite->pos_y = (float)player.y + 0.5;
	if (pos == 'N' || pos == 'S')
	{
		sprite->dir_y = (pos == 'N' ? -1 : 1);
		sprite->plane_x = (pos == 'N' ? 0.60 : -0.66);
	}
	else if (pos == 'W' || pos == 'E')
	{
		sprite->dir_x = (pos == 'W' ? -1 : 1);
		sprite->plane_y = (pos == 'W' ? -0.60 : 0.60);
	}
}

static t_game	setup(t_game game)
{
	game.player.x = game.cub->gen.x_player * TILE_SIZE;
	game.player.y = game.cub->gen.y_player * TILE_SIZE;
	game.player.ad_direction = 0;
	game.player.ws_direction = 0;
	game.player.rot_angle = define_dir(game.cub->gen.rot_angle);
	game.player.ad_speed = 15 * (PI / 180);
	game.player.ws_speed = 15;
	game.cub->gen.window_width = game.cub->gen.cols * TILE_SIZE;
	game.cub->gen.window_height = game.cub->gen.rows * TILE_SIZE;
	//sprite_start
	define_dir_plane(game.cub->gen.rot_angle, &game.sprite, game.player);
	game.sprite.zbuffer = malloc(game.cub->width * sizeof(float));
	game.sprite.amount = 1;
	game.sprite.order = malloc(game.sprite.amount * sizeof(int));
	//sprite_end
	game.ray = malloc(game.cub->width * sizeof(t_ray));
	game.textures = init_textures(game.vars, game.cub);
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

static int	x_exit(t_game *game)
{
	game_print_exit(CLOSECL, 1, *game);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_game	game;

	//test bzero
	ft_bzero(&game, sizeof(t_game));
	game_validateargs(argc, argv, &game);
	game.vars.init = mlx_init();
	game.cub = cub_analyzecub(argv[1]);
	game_validatescreen(game.vars, game.cub);
	game.vars.window = mlx_new_window(game.vars.init, game.cub->width,
			game.cub->height, "cub3d");
	game = setup(game);
	game_loop(0, &game);

	mlx_hook(game.vars.window, E_KEYPRESS, M_KEYPRESS, game_loop, &game);
	mlx_hook(game.vars.window, E_KEYRELEASE, M_KEYRELEASE, release_button, &game);
	mlx_hook(game.vars.window, E_KEYDESTROY, M_KEYDESTROY, x_exit, &game);
	mlx_loop(game.vars.init);
	return (0);
}
