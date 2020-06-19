/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:23:13 by caio              #+#    #+#             */
/*   Updated: 2020/06/19 15:17:03 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	search_wall(t_grid_vars *vars, t_ray_vars ray, int time, char **map,
		t_gen gen)
{
	while (vars->next_touch_x >= 0 && vars->next_touch_x <= gen.window_width &&
		vars->next_touch_y >= 0 && vars->next_touch_y <= gen.window_height)
	{
		ray.x_to_check = (time == 0) ? vars->next_touch_x :
			vars->next_touch_x + ((ray.facing_left) ? -1 : 0);
		ray.y_to_check = (time == 1) ? vars->next_touch_y :
			vars->next_touch_y + ((ray.facing_up) ? -1 : 0);
		if (is_walkable(ray.x_to_check, ray.y_to_check, map, gen))
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

void	horz_grid(t_ray_vars *ray, t_grid_vars *horz, t_player player, char
		**map, t_gen gen)
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
	search_wall(horz, *ray, 0, map, gen);
}

void	vert_grid(t_ray_vars *ray, t_grid_vars *vert, t_player player, char
		**map, t_gen gen)
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
	search_wall(vert, *ray, 1, map, gen);
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
	all->ray[ray.id].angle = ray.angle;
	all->ray[ray.id].facing_down = ray.facing_down;
	all->ray[ray.id].facing_up = ray.facing_up;
	all->ray[ray.id].facing_left = ray.facing_left;
	all->ray[ray.id].facing_right = ray.facing_right;
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
	horz_grid(&ray, &horz, all->player, all->cub->map, all->cub->gen);
	vert_grid(&ray, &vert, all->player, all->cub->map, all->cub->gen);
	choose_smallest_distance(horz, vert, ray, all);
}
