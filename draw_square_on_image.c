/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square_on_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:25:51 by caio              #+#    #+#             */
/*   Updated: 2020/05/29 13:26:03 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square_on_image(t_data *data, int size, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x <= size)
	{
		my_mlx_pixel_put(data, x, y, color);
		if (y++ == size)
		{
			y = 0;
			x++;
		}
	}
}

