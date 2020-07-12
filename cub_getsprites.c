/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_getsprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:48:54 by caio              #+#    #+#             */
/*   Updated: 2020/07/10 21:20:31 by caio             ###   ########.fr       */
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
	//free on the end
	gen->sprites = malloc(sprites * sizeof(t_sprites_pos));
	while (y < gen->rows)
	{
		while (x < gen->cols)
		{
			if (map[y][x] == '2')
			{
				gen->sprites[z].x = x;
				gen->sprites[z].y = y;
				z++;
				if (z == sprites)
					break ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
