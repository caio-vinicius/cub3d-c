/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_walkable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:19:25 by caio              #+#    #+#             */
/*   Updated: 2020/06/16 18:07:19 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable(float x, float y, char **map)
{
	int x_map;
	int y_map;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (0);
	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if (map[y_map][x_map] == '0' || map[y_map][x_map] == 'N' ||
			map[y_map][x_map] == 'S' || map[y_map][x_map] == 'E' ||
			map[y_map][x_map] == 'W')
		return (1);
	return (0);
}

