/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_iswalkable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:19:25 by caio              #+#    #+#             */
/*   Updated: 2020/07/20 14:40:42 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_iswalkable(float x, float y, char **map, t_gen gen)
{
	int x_map;
	int y_map;

	if (x < 0 || x > gen.window_width || y < 0 || y > gen.window_height)
		return (0);
	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if (map[y_map][x_map] == '0' || map[y_map][x_map] == 'N' ||
			map[y_map][x_map] == 'S' || map[y_map][x_map] == 'E' ||
			map[y_map][x_map] == 'W' || map[y_map][x_map] == '2')
		return (1);
	return (0);
}
