/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/05/28 13:35:08 by caio             ###   ########.fr       */
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

	size = 3 * MINIMAP_SCALE;
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
		(all.player.x + cos(all.player.rot_angle) * 10) * MINIMAP_SCALE,
		(all.player.y + sin(all.player.rot_angle) * 10) * MINIMAP_SCALE,
		all.vars);
}

void	render(t_all all)
{
	render_player(all);
	render_map(all.vars);
}

int is_walkable(float x, float y)
{
	int x_map;
	int y_map;
	
	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if (map[y_map][x_map] == 0)
		return (1);
	return (0);
}

void move_player(t_player *player)
{
	float move_step;
	float new_x;
	float new_y;
	
	//rotation	
	player->rot_angle += player->ad_direction * player->ad_speed;
	//walk
	move_step = player->ws_direction * player->ws_speed;
	new_x = player->x + cos(player->rot_angle) * move_step;
	new_y = player->y + sin(player->rot_angle) * move_step;
	new_x = ceil(new_x);
	new_y = ceil(new_y);
	if (is_walkable(new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}	
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

float	distance_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	cast_ray(float ray_angle, int id, t_player player)
{
	int ray_facing_down;
	int ray_facing_up;
	int ray_facing_right;
	int ray_facing_left;
	
	float xintercept;
	float yintercept;
	float xstep;
	float ystep;
	
	//horizontal	
	int found_horz_wall_hit;
	float horz_wall_hit_x;
	float horz_wall_hit_y;
	int horz_wall_content;

	float next_horz_touch_x;
	float next_horz_touch_y;
	
	ray_angle = normalize_angle(ray_angle);	
	ray_facing_down = ray_angle > 0 && ray_angle < PI;
	ray_facing_up = !ray_facing_down;
	ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	ray_facing_left = !ray_facing_right;
	
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += (ray_facing_down) ? TILE_SIZE : 0;

	xintercept = player.x + (yintercept - player.y) / tan(ray_angle);

	ystep = TILE_SIZE;
	ystep *= (ray_facing_up) ? -1 : 1;

	xstep = TILE_SIZE / tan(ray_angle);
	xstep *= (ray_facing_left && xstep > 0) ? -1 : 1;
	xstep *= (ray_facing_right && xstep < 0) ? -1 : 1;

	next_horz_touch_x = xintercept;
	next_horz_touch_y = yintercept;

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= WINDOW_WIDTH &&
		next_horz_touch_y >= 0 && next_horz_touch_y <= WINDOW_HEIGHT)
	{
		float x_to_check = next_horz_touch_x;
		float y_to_check = next_horz_touch_y + ((ray_facing_up) ? -1 : 0);
		
		if (is_walkable(x_to_check, y_to_check))
		{
			next_horz_touch_x += xstep;
			next_horz_touch_y += ystep;
		}
		else
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			horz_wall_content = map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			found_horz_wall_hit = 1;
			break;
		}
	}
	//vertical
	int found_vert_wall_hit;
	float vert_wall_hit_x;
	float vert_wall_hit_y;
	int vert_wall_content;
	float next_vert_touch_x;
	float next_vert_touch_y;
	
	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += (ray_facing_right) ? TILE_SIZE : 0;

	yintercept = player.y + (xintercept - player.x) / tan(ray_angle);

	xstep = TILE_SIZE;
	xstep *= (ray_facing_left) ? -1 : 1;

	ystep = TILE_SIZE / tan(ray_angle);
	ystep *= (ray_facing_up && xstep > 0) ? -1 : 1;
	ystep *= (ray_facing_down && xstep < 0) ? -1 : 1;

	next_vert_touch_x = xintercept;
	next_vert_touch_y = yintercept;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= WINDOW_WIDTH &&
		next_vert_touch_y >= 0 && next_vert_touch_y <= WINDOW_HEIGHT)
	{
		float x_to_check = next_vert_touch_x + ((ray_facing_left) ? -1 : 0);
		float y_to_check = next_vert_touch_y;
		if (is_walkable(x_to_check, y_to_check))
		{
			next_vert_touch_x += xstep;
			next_vert_touch_y += ystep;
		}
		else
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			found_vert_wall_hit = 1;
			break;
		}
	}

	float horz_hit_distance;
	float vert_hit_distance;

	if (found_horz_wall_hit)
	{
		horz_hit_distance = distance_points(player.x, player.y,
			horz_wall_hit_x, horz_wall_hit_y);
	}
	else
		horz_hit_distance = INT_MAX;
	if (found_vert_wall_hit)
	{
		vert_hit_distance = distance_points(player.x, player.y,
			vert_wall_hit_x, vert_wall_hit_y);
	}
	else
		vert_hit_distance = INT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		ray[id].distance = vert_hit_distance;
		ray[id].wall_hit_x = vert_wall_hit_x;
		ray[id].wall_hit_y = vert_wall_hit_y;
		ray[id].wall_hit_content = vert_wall_content;	
		ray[id].was_hit_vertical = 1;
	}
	else
	{
		ray[id].distance = vert_hit_distance;
		ray[id].wall_hit_x = vert_wall_hit_x;
		ray[id].wall_hit_y = vert_wall_hit_y;
		ray[id].wall_hit_content = vert_wall_content;	
		ray[id].was_hit_vertical = 0;
	}
	ray[id].ray_angle = ray_angle;
	ray[id].ray_facing_down = ray_facing_down;	
	ray[id].ray_facing_up = ray_facing_up;	
	ray[id].ray_facing_left = ray_facing_left;	
	ray[id].ray_facing_right = ray_facing_right;	
}

void	cast_all_rays(t_player *player)
{
	float ray_angle;
	int id;

	id = 0;
	ray_angle = player->rot_angle - (FOV_ANGLE / 2); 
	while (id < NUM_RAYS)
	{
		cast_ray(ray_angle, id, *player);
		ray_angle += FOV_ANGLE / NUM_RAYS;		
		id++;
	}
}

void	update(t_all *all)
{
	move_player(&all->player);
	cast_all_rays(&all->player);
}

t_all	setup(t_all all)
{
	all.player.x = WINDOW_WIDTH / 2;
	all.player.y = WINDOW_HEIGHT / 2;
	all.player.ad_direction = 0;
	all.player.ws_direction = 0;
	all.player.rot_angle = PI / 2;
	all.player.ad_speed = 45 * (PI / 180);
	all.player.ws_speed = 5;	
	return (all);
}

void	process_keys(int keycode, t_player *player)
{
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

int	release_button(int keycode, t_all *all)
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
		mlx_hook(all.vars.window, 3, 1L<<1, release_button, &all);
		//mlx_loop_hook(all.vars.init, game_loop, &all);
		mlx_loop(all.vars.init);
	}
}
