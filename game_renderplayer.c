/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderplayer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:40:49 by caio              #+#    #+#             */
/*   Updated: 2020/06/20 13:06:33 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(int x, int y, t_vars vars)
{
	t_data	data;
	int	size;
	//dont work properly, different image.
	size = 10 * MINIMAP_SCALE;
	data.img = mlx_new_image(vars.init, size, size);
	data.img_addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
		&data.endian);
	game_drawsquare(&data, size, PLAYER_COLOR);
	mlx_put_image_to_window(vars.init, vars.window, data.img, x, y);
	mlx_destroy_image(vars.init, data.img);
}

void	game_renderplayer(t_player player, t_vars vars)
{
	draw_player(player.x * MINIMAP_SCALE, player.y * MINIMAP_SCALE, vars);
	game_drawline(
		player.x * MINIMAP_SCALE,
		player.y * MINIMAP_SCALE,
		(player.x + cos(player.rot_angle) * 10) * MINIMAP_SCALE,
		(player.y + sin(player.rot_angle) * 10) * MINIMAP_SCALE,
		vars
	);
}
