/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_drawline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:34:31 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 17:27:57 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	sabs(int n)
{
	return ((n > 0) ? n : (n * (-1)));
}

void		game_drawline(t_draw_line vars, t_data *data)
{
	int		steps;
	float	x;
	float	y;
	int		i;

	i = 0;
	steps = sabs(vars.x1 - vars.x0) > sabs(vars.y1 - vars.y0) ?
		sabs(vars.x1 - vars.x0) : sabs(vars.y1 - vars.y0);
	x = vars.x0;
	y = vars.y0;
	while (i <= steps)
	{
		game_mlxpixelput(data, round(x), round(y), 0x0000ff);
		x += (vars.x1 - vars.x0) / (float)steps;
		y += (vars.y1 - vars.y0) / (float)steps;
		i++;
	}
}
