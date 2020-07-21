/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 17:34:15 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 20:20:50 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_horz_vert(t_grid_vars *vars)
{
	vars->found_wall_hit = 0;
	vars->wall_hit_x = 0;
	vars->wall_hit_y = 0;
	vars->wall_content = 0;
}

void	set_ray_vert(t_ray *ray, t_grid_vars vert, float vert_hit, int id)
{
	ray[id].distance = vert_hit;
	ray[id].wall_hit_x = vert.wall_hit_x;
	ray[id].wall_hit_y = vert.wall_hit_y;
	ray[id].wall_hit_content = vert.wall_content;
	ray[id].was_hit_vertical = 1;
}

void	set_ray_horz(t_ray *ray, t_grid_vars horz, float horz_hit, int id)
{
	ray[id].distance = horz_hit;
	ray[id].wall_hit_x = horz.wall_hit_x;
	ray[id].wall_hit_y = horz.wall_hit_y;
	ray[id].wall_hit_content = horz.wall_content;
	ray[id].was_hit_vertical = 0;
}

float	define_dir(char rot_angle)
{
	float dir;

	if (rot_angle == 'N')
		dir = (PI * 1.5);
	else if (rot_angle == 'S')
		dir = (PI / 2);
	else if (rot_angle == 'E')
		dir = TWO_PI;
	else if (rot_angle == 'W')
		dir = PI;
	else
		dir = (PI * 1.5);
	return (dir);
}

void	define_dir_plane(char pos, t_sprite *sprite)
{
	if (pos == 'N' || pos == 'S')
	{
		sprite->dir_y = (pos == 'N' ? -1 : 1);
		sprite->plane_x = (pos == 'N' ? 0.60 : -0.60);
	}
	else if (pos == 'W' || pos == 'E')
	{
		sprite->dir_x = (pos == 'W' ? -1 : 1);
		sprite->plane_y = (pos == 'W' ? -0.60 : 0.60);
	}
}
