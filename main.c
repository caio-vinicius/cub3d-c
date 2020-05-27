/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/05/27 12:34:53 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vars	init(t_vars vars)
{
	vars.init = mlx_init();
	vars.window = mlx_new_window(vars.init, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	return (vars);
}

void	draw_wall(int x, int y, t_all all)
{
	int width;
	int height;
	void *wall;
	static int i;
	
	wall = mlx_xpm_file_to_image(all.vars.init, "textures/brick.xpm", &width, &height);
	mlx_put_image_to_window(all.vars.init, all.vars.window, wall, x, y);
	mlx_destroy_image(all.vars.init, wall);
	printf("a wall was put %d\n", i++);
}

void	render_map(t_all all)
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
				draw_wall(y * TILE_SIZE, x * TILE_SIZE, all);
			y++;
		}
		y = 0;
		x++;
	} 
}

void	render(t_all all)
{
	render_map(all);
	//render_player(all);
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
