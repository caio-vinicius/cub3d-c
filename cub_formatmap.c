/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_formatmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:19:48 by caio              #+#    #+#             */
/*   Updated: 2020/06/16 17:54:56 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		find_biggest_line(char **ptr)
{
	int i;
	int y;
	int ptrlen;
	int strlen;
	ptrlen = cub_ptrlen(ptr);
	y = 0;
	strlen = 0;
	while (y < ptrlen)
	{
		i = strlen;
		strlen = ft_strlen(ptr[y]);
		if (strlen > i)
			i = strlen;
		else
			strlen = i;
		y++;
	}
	return (i);
}

char	**cub_formatmap(char **map, t_cub *cub)
{
	int x;
	int y;

	cub->gen.cols = find_biggest_line(map);
	cub->gen.rows = cub_ptrlen(map);
	y = 0;
	x = 0;
	while (y < cub->gen.rows)
	{
		map[y][cub->gen.cols] = '\0';
		while (x < cub->gen.cols)
		{
			if ((!(cub_ischarmap(map[y][x])) || map[y][x] == ' '))
				map[y][x] = '1';
			x++;
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' ||
					map[y][x] == 'W')
			{
				cub->gen.x_player = x;
				cub->gen.y_player = y;
				cub->gen.rot_angle = map[y][x];
			}

		}
		x = 0;
		y++;
	}
	return (map);
}
