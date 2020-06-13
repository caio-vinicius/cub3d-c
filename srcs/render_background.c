/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 12:42:53 by caio              #+#    #+#             */
/*   Updated: 2020/06/13 17:11:01 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_background(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < WINDOW_WIDTH)
	{
		while (j < WINDOW_HEIGHT / 2)
		{
			my_mlx_pixel_put(data, i, j, CEILING_COLOR);
			j++;
		}
		while (j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(data, i, j, FLOOR_COLOR);
			j++;
		}
		j = 0;
		i++;
	}
}
