/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_castray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:23:13 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 19:58:23 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			search_wall(t_grid_vars *vars, t_ray_vars ray, t_game game,
		int time)
{
	while (vars->next_touch_x >= 0 &&
			vars->next_touch_x <= game.cub->gen.window_width &&
			vars->next_touch_y >= 0 &&
			vars->next_touch_y <= game.cub->gen.window_height)
	{
		ray = find_coords_to_check(ray, vars, time);
		if (game_iswalkable(ray.x_to_check, ray.y_to_check, game.cub->map,
					game.cub->gen))
		{
			vars->next_touch_x += ray.xstep;
			vars->next_touch_y += ray.ystep;
		}
		else
		{
			vars->wall_hit_x = vars->next_touch_x;
			vars->wall_hit_y = vars->next_touch_y;
			vars->wall_content = game.cub->map[(int)floor(ray.y_to_check /
					TILE_SIZE)][(int)floor(ray.x_to_check / TILE_SIZE)];
			vars->found_wall_hit = 1;
			break ;
		}
	}
}

static void			horz_grid(t_ray_vars *ray, t_grid_vars *horz, t_game game)
{
	ray->yintercept = floor(game.player.y / TILE_SIZE) * TILE_SIZE;
	ray->yintercept += (ray->facing_down) ? TILE_SIZE : 0;
	ray->xintercept = game.player.x + (ray->yintercept - game.player.y) /
		tan(ray->angle);
	ray->ystep = TILE_SIZE;
	ray->ystep *= (ray->facing_up) ? -1 : 1;
	ray->xstep = TILE_SIZE / tan(ray->angle);
	ray->xstep *= (ray->facing_left && ray->xstep > 0) ? -1 : 1;
	ray->xstep *= (ray->facing_right && ray->xstep < 0) ? -1 : 1;
	horz->next_touch_x = ray->xintercept;
	horz->next_touch_y = ray->yintercept;
	search_wall(horz, *ray, game, 0);
}

static void			vert_grid(t_ray_vars *ray, t_grid_vars *vert, t_game game)
{
	ray->xintercept = floor(game.player.x / TILE_SIZE) * TILE_SIZE;
	ray->xintercept += (ray->facing_right) ? TILE_SIZE : 0;
	ray->yintercept = game.player.y + (ray->xintercept - game.player.x) *
		tan(ray->angle);
	ray->xstep = TILE_SIZE;
	ray->xstep *= (ray->facing_left) ? -1 : 1;
	ray->ystep = TILE_SIZE * tan(ray->angle);
	ray->ystep *= (ray->facing_up && ray->ystep > 0) ? -1 : 1;
	ray->ystep *= (ray->facing_down && ray->ystep < 0) ? -1 : 1;
	vert->next_touch_x = ray->xintercept;
	vert->next_touch_y = ray->yintercept;
	search_wall(vert, *ray, game, 1);
}

static void			choose_smallest_distance(t_grid_vars horz, t_grid_vars vert,
		t_ray_vars ray, t_game *game)
{
	float horz_hit_distance;
	float vert_hit_distance;

	horz_hit_distance = (horz.found_wall_hit) ? game_distancepoints(
			game->player.x, game->player.y, horz.wall_hit_x, horz.wall_hit_y) :
		INT_MAX;
	vert_hit_distance = (vert.found_wall_hit) ? game_distancepoints(
			game->player.x, game->player.y, vert.wall_hit_x, vert.wall_hit_y) :
		INT_MAX;
	if (vert_hit_distance < horz_hit_distance)
		set_ray_vert(game->ray, vert, vert_hit_distance, ray.id);
	else
		set_ray_horz(game->ray, horz, horz_hit_distance, ray.id);
	game->ray[ray.id].angle = ray.angle;
	game->ray[ray.id].facing_down = ray.facing_down;
	game->ray[ray.id].facing_up = ray.facing_up;
	game->ray[ray.id].facing_left = ray.facing_left;
	game->ray[ray.id].facing_right = ray.facing_right;
}

void				game_castray(float ray_angle, int id, t_game *game)
{
	t_ray_vars	ray;
	t_grid_vars	horz;
	t_grid_vars	vert;

	ray.angle = game_normalizeangle(ray_angle);
	ray.facing_down = ray.angle > 0 && ray.angle < PI;
	ray.facing_up = !ray.facing_down;
	ray.facing_right = ray.angle < 0.5 * PI || ray.angle > 1.5 * PI;
	ray.facing_left = !ray.facing_right;
	ray.id = id;
	init_horz_vert(&horz);
	init_horz_vert(&vert);
	horz_grid(&ray, &horz, *game);
	vert_grid(&ray, &vert, *game);
	choose_smallest_distance(horz, vert, ray, game);
}
