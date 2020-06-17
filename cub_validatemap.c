/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validatemap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:22:50 by caio              #+#    #+#             */
/*   Updated: 2020/06/17 09:29:49 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_validatemap(char **map)
{
	int x;
	int y;
	int strlen;
	int ptrlen;

	x = 0;
	y = 0;
	ptrlen = cub_ptrlen(map);
	while (y < ptrlen - 1) //linha
	{
		strlen = ft_strlen(map[y]);
		while (x < strlen) //coluna
		{
			if (((y == 0 || y == ptrlen - 1) || (x == 0 || x == strlen - 1)) &&
					(!(cub_iswall(map[y][x]))))
				print_exit(ENSURRW, 2);
			if ((y > 0 && y < ptrlen - 1) && (x > 0 && x < strlen - 1) &&
					(map[y][x] == '0') && ((!(cub_ischarmap(map[y - 1][x]))) ||
					(!(cub_ischarmap(map[y + 1][x]))) ||
					(!(cub_ischarmap(map[y][x - 1]))) ||
					(!(cub_ischarmap(map[y][x + 1])))))
				print_exit(ENSURRW, 2);
			x++;
		}
		x = 0;
		y++;
	}
}
