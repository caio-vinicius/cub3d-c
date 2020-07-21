/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mlxpixelput.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 19:53:24 by caio              #+#    #+#             */
/*   Updated: 2020/07/20 14:43:16 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_mlxpixelput(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->img_addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}
