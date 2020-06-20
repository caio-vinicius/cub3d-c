/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_formatmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:19:48 by caio              #+#    #+#             */
/*   Updated: 2020/06/20 12:41:30 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int		find_biggest_line(char **ptr)
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

char	**cub_formatmap(char **map, t_gen *gen)
{
	int x;
	int y;

	gen->cols = find_biggest_line(map);
	gen->rows = cub_ptrlen(map);
	y = 0;
	x = 0;
	while (y < gen->rows)
	{
		map[y][gen->cols] = '\0';
		while (x < gen->cols)
		{
			if ((!(cub_ischarmap(map[y][x])) || map[y][x] == ' '))
				map[y][x] = '1';
			x++;
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' ||
					map[y][x] == 'W')
			{
				gen->x_player = x;
				gen->y_player = y;
				gen->rot_angle = map[y][x];
			}

		}
		x = 0;
		y++;
	}
	return (map);
}
