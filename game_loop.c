/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:37:17 by caio              #+#    #+#             */
/*   Updated: 2020/06/01 15:50:30 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	render_graph(t_all all)
{
	t_data data;
	int i;
	int j;
	
	i = 0;
	j = 0;	
	data.img = mlx_new_image(all.vars.init, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img_addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
		&data.endian);
	while (i < WINDOW_WIDTH)
	{
		while (j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(&data, i, j, 0xFFFF00);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(all.vars.init, all.vars.window, data.img, 0, 0);
}*/

void	draw_strip(t_data *data, t_all all, t_wall wall, int i)
{
	int x;
	int y;
	
	x = 0 + (WALL_STRIP_WIDTH * i);
	y = wall.top_pixel;
	while (y <= wall.bottom_pixel)
	{
		my_mlx_pixel_put(data, x, y, 0xffffff);
		x++;
		if (x == WALL_STRIP_WIDTH + (WALL_STRIP_WIDTH * i))
		{
			x = 0 + (WALL_STRIP_WIDTH * i);
			y++;
		}
	}
}

void	render_walls(t_all all)
{
	int i;
	static int k;
	t_data data;
	t_wall wall;

	i = 0;
	data.img = mlx_new_image(all.vars.init, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img_addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
		&data.endian);
	while (i < NUM_RAYS)
	{
		wall.perp_distance = all.ray[i].distance * cos(all.ray[i].ray_angle - all.player.rot_angle);
		wall.distance_projection_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		wall.projected_height = (TILE_SIZE / wall.perp_distance) * wall.distance_projection_plane;

		wall.strip_height = (int)wall.projected_height;

		wall.top_pixel = (WINDOW_HEIGHT / 2) - (wall.strip_height / 2);
		wall.top_pixel = (wall.top_pixel < 0) ? 0 : wall.top_pixel;
		wall.bottom_pixel = (WINDOW_HEIGHT / 2) + (wall.strip_height / 2);
		wall.bottom_pixel = (wall.bottom_pixel > WINDOW_HEIGHT) ? WINDOW_HEIGHT : wall.bottom_pixel;
		
		//printf("wall_strip_height %f wall_top_pixel %d wall_bottom_pixel %d\n%d\n", wall.projected_height, wall.top_pixel, wall.bottom_pixel, k);
		
		draw_strip(&data, all, wall, i);
		i++;
	}
	k++;
	mlx_put_image_to_window(all.vars.init, all.vars.window, data.img, 0, 0);
	mlx_destroy_image(all.vars.init, data.img);	
}

void	render(t_all all)
{
			
	//render_graph(all);
	render_walls(all);
	render_map(all.vars);
	//render_player(all);
	render_rays(&all);
}

void	update(t_all *all)
{
	move_player(&all->player);
	cast_all_rays(all);
}

void	process_keys(int keycode, t_player *player)
{
	//printf("%d\n", keycode);
	if (keycode == UP_ARROW)
		player->ws_direction = 1;
	else if (keycode == DOWN_ARROW)
		player->ws_direction = -1;
	else if (keycode == LEFT_ARROW)
		player->ad_direction = -1;
	else if (keycode == RIGHT_ARROW)
		player->ad_direction = 1;
}

int	game_loop(int keycode, t_all *all)
{
	process_keys(keycode, &all->player);
	update(all);
	render(*all);
}
