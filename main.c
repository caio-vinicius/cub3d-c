/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/05/29 13:07:45 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

t_vars	init(t_vars vars)
{
	vars.init = mlx_init();
	vars.window = mlx_new_window(vars.init, WINDOW_WIDTH, WINDOW_HEIGHT,
		"cub3d");
	return (vars);
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
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	is_walkable(float x, float y)
{
	int x_map;
	int y_map;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (0);
	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if (map[y_map][x_map] == 0)
		return (1);
	return (0);
}

void	search_wall(t_grid_vars *vars, t_ray_vars ray, int time)
{
	while (vars->next_touch_x >= 0 && vars->next_touch_x <= WINDOW_WIDTH &&
		vars->next_touch_y >= 0 && vars->next_touch_y <= WINDOW_HEIGHT)
	{
		ray.x_to_check = (time == 1) ? vars->next_touch_x +
			((ray.facing_left) ? -1 : 0) : vars->next_touch_x;
		ray.y_to_check = (time == 1) ? vars->next_touch_y :
			vars->next_touch_y + ((ray.facing_up) ? -1 : 0);
		if (is_walkable(ray.x_to_check, ray.y_to_check))
		{
			vars->next_touch_x += ray.xstep;
			vars->next_touch_y += ray.ystep;
		}
		else
		{
			vars->wall_hit_x = vars->next_touch_x;
			vars->wall_hit_y = vars->next_touch_y;
			vars->wall_content = map[(int)floor(ray.y_to_check / TILE_SIZE)]
				[(int)floor(ray.x_to_check / TILE_SIZE)];
			vars->found_wall_hit = 1;
			break ;
		}
	}
}

void	horz_grid(t_ray_vars *ray, t_grid_vars *horz, t_player player)
{
	ray->yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	ray->yintercept += (ray->facing_down) ? TILE_SIZE : 0;
	ray->xintercept = player.x + (ray->yintercept - player.y) / tan(ray->angle);
	ray->ystep = TILE_SIZE;
	ray->ystep *= (ray->facing_up) ? -1 : 1;
	ray->xstep = TILE_SIZE / tan(ray->angle);
	ray->xstep *= (ray->facing_left && ray->xstep > 0) ? -1 : 1;
	ray->xstep *= (ray->facing_right && ray->xstep < 0) ? -1 : 1;
	horz->next_touch_x = ray->xintercept;
	horz->next_touch_y = ray->yintercept;
	search_wall(horz, *ray, 0);
}

void	vert_grid(t_ray_vars *ray, t_grid_vars *vert, t_player player)
{
	ray->xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	ray->xintercept += (ray->facing_right) ? TILE_SIZE : 0;
	ray->yintercept = player.y + (ray->xintercept - player.x) * tan(ray->angle);
	ray->xstep = TILE_SIZE;
	ray->xstep *= (ray->facing_left) ? -1 : 1;
	ray->ystep = TILE_SIZE * tan(ray->angle);
	ray->ystep *= (ray->facing_up && ray->ystep > 0) ? -1 : 1;
	ray->ystep *= (ray->facing_down && ray->ystep < 0) ? -1 : 1;
	vert->next_touch_x = ray->xintercept;
	vert->next_touch_y = ray->yintercept;
	search_wall(vert, *ray, 1);
}

void	init_horz_vert(t_grid_vars *vars)
{
	vars->found_wall_hit = 0;
	vars->wall_hit_x = 0;
	vars->wall_hit_y = 0;
	vars->wall_content = 0;
}

void	set_ray_vert(t_all *all, t_grid_vars vert, float vert_hit, int id)
{
	all->ray[id].distance = vert_hit;
	all->ray[id].wall_hit_x = vert.wall_hit_x;
	all->ray[id].wall_hit_y = vert.wall_hit_y;
	all->ray[id].wall_hit_content = vert.wall_content;
	all->ray[id].was_hit_vertical = 1;
}

void	set_ray_horz(t_all *all, t_grid_vars horz, float horz_hit, int id)
{
	all->ray[id].distance = horz_hit;
	all->ray[id].wall_hit_x = horz.wall_hit_x;
	all->ray[id].wall_hit_y = horz.wall_hit_y;
	all->ray[id].wall_hit_content = horz.wall_content;
	all->ray[id].was_hit_vertical = 0;
}

void	choose_smallest_distance(t_grid_vars horz, t_grid_vars vert, t_ray_vars ray, t_all *all)
{
	float horz_hit_distance;
	float vert_hit_distance;

	horz_hit_distance = (horz.found_wall_hit) ? distance_points(all->player.x,
		all->player.y, horz.wall_hit_x, horz.wall_hit_y) : INT_MAX;
	vert_hit_distance = (vert.found_wall_hit) ? distance_points(all->player.x,
		all->player.y, vert.wall_hit_x, vert.wall_hit_y) : INT_MAX;
	if (vert_hit_distance < horz_hit_distance)
		set_ray_vert(all, vert, vert_hit_distance, ray.id);
	else
		set_ray_horz(all, horz, horz_hit_distance, ray.id);
	all->ray[ray.id].ray_angle = ray.angle;
	all->ray[ray.id].ray_facing_down = ray.facing_down;
	all->ray[ray.id].ray_facing_up = ray.facing_up;
	all->ray[ray.id].ray_facing_left = ray.facing_left;
	all->ray[ray.id].ray_facing_right = ray.facing_right;
}

void	cast_ray(float ray_angle, int id, t_all *all)
{
	t_ray_vars	ray;
	t_grid_vars	horz;
	t_grid_vars	vert;

	ray.angle = normalize_angle(ray_angle);
	ray.facing_down = ray.angle > 0 && ray.angle < PI;
	ray.facing_up = !ray.facing_down;
	ray.facing_right = ray.angle < 0.5 * PI || ray.angle > 1.5 * PI;
	ray.facing_left = !ray.facing_right;
	ray.id = id;
	init_horz_vert(&horz);
	init_horz_vert(&vert);
	horz_grid(&ray, &horz, all->player);
	vert_grid(&ray, &vert, all->player);
	choose_smallest_distance(horz, vert, ray, all);
}

void	cast_all_rays(t_all *all)
{
	float	ray_angle;
	int	id;

	id = 0;
	ray_angle = all->player.rot_angle - (FOV_ANGLE / 2);
	while (id < NUM_RAYS)
	{
		cast_ray(ray_angle, id, all);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		id++;
	}
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
	t_data	data;
	int	size;

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
	t_data	data;
	int	size;

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
	draw_player(all.player.x * MINIMAP_SCALE, all.player.y * MINIMAP_SCALE,
		all.vars);
	dda_draw_line(
		all.player.x * MINIMAP_SCALE,
		all.player.y * MINIMAP_SCALE,
		(all.player.x + cos(all.player.rot_angle) * 10) * MINIMAP_SCALE,
		(all.player.y + sin(all.player.rot_angle) * 10) * MINIMAP_SCALE,
		all.vars);
}

void	render_rays(t_all *all)
{
	int i;

	i = 0;
	while (i < NUM_RAYS)
	{
		dda_draw_line(MINIMAP_SCALE * all->player.x,
			MINIMAP_SCALE * all->player.y,
			MINIMAP_SCALE * all->ray[i].wall_hit_x,
			MINIMAP_SCALE * all->ray[i].wall_hit_y, all->vars);
		i++;
	}
}

void	render(t_all all)
{
	render_player(all);
	render_rays(&all);
	render_map(all.vars);
}

void	move_player(t_player *player)
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

void	update(t_all *all)
{
	move_player(&all->player);
	cast_all_rays(all);
}

t_all	setup(t_all all)
{
	all.player.x = WINDOW_WIDTH / 2;
	all.player.y = WINDOW_HEIGHT / 2;
	all.player.ad_direction = 0;
	all.player.ws_direction = 0;
	all.player.rot_angle = PI / 2;
	all.player.ad_speed = 5 * (PI / 180);
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
		mlx_hook(all.vars.window, 2, 1L << 0, game_loop, &all);
		mlx_hook(all.vars.window, 3, 1L << 1, release_button, &all);
		//mlx_loop_hook(all.vars.init, game_loop, &all);
		mlx_loop(all.vars.init);
	}
}
