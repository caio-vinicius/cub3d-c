/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/05/27 22:13:36 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,1,1},
	{1,1,1,1,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,1,1},
	{1,0,0,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};

t_vars	init(t_vars vars)
{
	vars.init = mlx_init();
	vars.window = mlx_new_window(vars.init, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	return (vars);
}

void	draw_square_on_image(t_data *data, int size, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x <= size)
	{
		my_mlx_pixel_put(data, x, y, color);
		if (y++ == size)
		{
			y = 0;
			x++;
		}
	}
}

void	draw_wall(int x, int y, t_vars vars)
{
	t_data data;
	int size;

	size = TILE_SIZE * MINIMAP_SCALE;
	data.img = mlx_new_image(vars.init, size, size);
	data.img_addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
		&data.endian);	
	draw_square_on_image(&data, size, 0xffffff);
	mlx_put_image_to_window(vars.init, vars.window, data.img, x, y);
	mlx_destroy_image(vars.init, data.img);
}

void	render_map(t_vars vars)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < MAP_NUM_ROWS)
	{
		while (y < MAP_NUM_COLS)
		{
			if (map[x][y] == 1)
				draw_wall((y * TILE_SIZE) * MINIMAP_SCALE,
					(x * TILE_SIZE) * MINIMAP_SCALE, vars);
			y++;
		}
		y = 0;
		x++;
	} 
}

void	draw_player(int x, int y, t_vars vars)
{
	t_data data;
	int size;

	size = 10 * MINIMAP_SCALE;
	data.img = mlx_new_image(vars.init, size, size);
	data.img_addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
		&data.endian);	
	draw_square_on_image(&data, size, 0xff0000);
	mlx_put_image_to_window(vars.init, vars.window, data.img, x, y);
	mlx_destroy_image(vars.init, data.img);
}

void	render_player(t_all all)
{	
	mlx_clear_window(all.vars.init, all.vars.window);
	draw_player(all.player.x * MINIMAP_SCALE, all.player.y * MINIMAP_SCALE, all.vars);
	dda_draw_line(
		all.player.x * MINIMAP_SCALE,
		all.player.y * MINIMAP_SCALE,
		(all.player.x + cos(all.player.rot_angle) * 20) * MINIMAP_SCALE,
		(all.player.y + sin(all.player.rot_angle) * 20) * MINIMAP_SCALE,
		all.vars);
}

void	render(t_all all)
{
	render_player(all);
	render_map(all.vars);
}

void	update(t_player *player)
{
	player->rot_angle += player->ad_direction * player->ad_speed;
}

t_all	setup(t_all all)
{
	all.player.x = WINDOW_WIDTH / 2;
	all.player.y = WINDOW_HEIGHT / 2;
	all.player.ad_direction = 0;
	all.player.ws_direction = 0;
	all.player.rot_angle = PI / 2;
	all.player.ad_speed = 5 * (PI / 180);
	all.player.ws_speed = 50;	
	return (all);
}

void	process_keys(int keycode, t_player *player)
{
	if (keycode == UP_ARROW)
		player->ws_direction = 0;
	else if (keycode == DOWN_ARROW)
		player->ws_direction = 0;
	else
		player->ws_direction = 0;	
	if (keycode == LEFT_ARROW)
		player->ad_direction = -1;
	else if (keycode == RIGHT_ARROW)
		player->ad_direction = 1;
	else
		player->ad_direction = 0;
}

int	game_loop(int keycode, t_all *all)
{
	process_keys(keycode, &all->player);
	update(&all->player);
	render(*all);
}

int	main(void)
{
	t_all all;

	all.vars = init(all.vars);	
	all = setup(all);
	game_loop(0, &all);
	
	if (all.vars.init && all.vars.window)
	{
		mlx_hook(all.vars.window, 2, 1L<<0, game_loop, &all);
		//mlx_loop_hook(all.vars.init, game_loop, &all);
		mlx_loop(all.vars.init);
	}
}
