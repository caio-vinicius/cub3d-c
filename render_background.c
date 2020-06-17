/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 12:42:53 by caio              #+#    #+#             */
/*   Updated: 2020/06/17 11:20:16 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_background(t_data *data, t_cub cub)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < cub.width)
	{
		while (j < cub.height / 2)
		{
			my_mlx_pixel_put(data, i, j, CEILING_COLOR);
			j++;
		}
		while (j < cub.height)
		{
			my_mlx_pixel_put(data, i, j, FLOOR_COLOR);
			j++;
		}
		j = 0;
		i++;
	}
}
