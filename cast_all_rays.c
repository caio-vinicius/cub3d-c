/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:34:30 by caio              #+#    #+#             */
/*   Updated: 2020/06/17 18:10:22 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_all_rays(t_all *all)
{
	float	ray_angle;
	int	id;

	id = 0;
	ray_angle = all->player.rot_angle - (FOV_ANGLE / 2);
	while (id < all->cub.width)
	{
		cast_ray(ray_angle, id, all);
		ray_angle += FOV_ANGLE / all->cub.width;
		id++;
	}
}
