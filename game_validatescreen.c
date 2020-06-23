/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_validatescreen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:06:29 by caio              #+#    #+#             */
/*   Updated: 2020/06/23 12:06:45 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_validatescreen(int argc, t_vars vars, t_cub *cub)
{
	int width;
	int height;

	(void)argc;
	mlx_get_screen_size(vars.init, &width, &height);
	if (cub->width > (unsigned int)width)
		cub->width = width;
	if (cub->height > (unsigned int)height)
		cub->height = height;
}
