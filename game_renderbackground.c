/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderbackground.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 12:42:53 by caio              #+#    #+#             */
/*   Updated: 2020/06/20 12:54:22 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_renderbackground(t_data *data, t_cub *cub)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (i < cub->width)
	{
		while (j < cub->height / 2)
		{
			game_mlxpixelput(data, i, j, cub->ceiling);
			j++;
		}
		while (j < cub->height)
		{
			game_mlxpixelput(data, i, j, cub->floor);
			j++;
		}
		j = 0;
		i++;
	}
}
