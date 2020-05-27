/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/05/27 15:18:30 by caio             ###   ########.fr       */
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
	draw_player(all.player.x * MINIMAP_SCALE, all.player.y * MINIMAP_SCALE, all.vars);
}

void	render(t_all all)
{
	render_map(all.vars);
	render_player(all);
}

t_player	update(t_player player)
{
	return (player);
}

t_all	setup(t_all all)
{
	all.player.x = WINDOW_WIDTH / 2;
	all.player.y = WINDOW_HEIGHT / 2;
	all.player.ad_direction = 0;
	all.player.ws_direction = 0;
	all.player.rot_angle = PI / 2;
	all.player.ad_speed = 45 * (PI / 180);
	all.player.ws_speed = 50;	
	return (all);
}

void	process_keys(int keycode, t_vars vars)
{
	if (keycode == 65308)
		mlx_destroy_window(vars.init, vars.window);
}

int	game_loop(int keycode, t_all *all)
{
	//sleep(1);
	process_keys(keycode, all->vars);
	all->player = update(all->player);
	render(*all);
	//printf("x %d y %d\n", all->player.x, all->player.y);
}

int	main(void)
{
	t_all all;

	all.vars = init(all.vars);	
	all = setup(all);
	game_loop(0, &all);
	
	if (all.vars.init && all.vars.window)
	{
		mlx_hook(all.vars.window, E_KEYPRESS, M_KEYPRESS, game_loop, &all);
		//mlx_loop_hook(all.vars.init, game_loop, &all);
		mlx_loop(all.vars.init);
	}
}
