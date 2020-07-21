/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_getsprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:48:54 by caio              #+#    #+#             */
/*   Updated: 2020/07/20 14:25:35 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_getsprites(char **map, t_gen *gen)
{
	int sprites;
	int x;
	int y;
	int z;

	x = 0;
	y = 0;
	z = 0;
	sprites = gen->amount_sprites;
	gen->sprites = malloc(sprites * sizeof(t_sprites_pos));
	while (y < gen->rows)
	{
		while (x++ < gen->cols)
		{
			if (map[y][x] == '2')
			{
				gen->sprites[z].x = x;
				gen->sprites[z].y = y;
				if (z++ == sprites)
					break ;
			}
		}
		x = 0;
		y++;
	}
}
