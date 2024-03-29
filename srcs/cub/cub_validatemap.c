/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validatemap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:22:50 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 17:15:30 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	is_surrounded_by_walls(int x, int y, int strlen, char **map)
{
	int ptrlen;

	ptrlen = cub_ptrlen(map);
	if (((y == 0 || y == ptrlen - 1) || (x == 0 || x == strlen - 1)) &&
			(!(cub_iswall(map[y][x]))))
		cub_print_exit(ENSURRW);
	if ((y > 0 && y < ptrlen - 1) && (x > 0 && x < strlen - 1) &&
		(map[y][x] == '0') && ((!(cub_ischarmap(map[y - 1][x]))) ||
		(!(cub_ischarmap(map[y + 1][x]))) ||
		(!(cub_ischarmap(map[y][x - 1]))) ||
		(!(cub_ischarmap(map[y][x + 1])))))
		cub_print_exit(ENSURRW);
}

void		cub_validatemap(char **map)
{
	int x;
	int y;
	int strlen;
	int ptrlen;

	x = 0;
	y = 0;
	ptrlen = cub_ptrlen(map);
	while (y < ptrlen - 1)
	{
		strlen = ft_strlen(map[y]);
		while (x < strlen)
		{
			is_surrounded_by_walls(x, y, strlen, map);
			x++;
		}
		x = 0;
		y++;
	}
}
