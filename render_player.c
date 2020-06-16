/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:40:49 by caio              #+#    #+#             */
/*   Updated: 2020/06/02 12:41:55 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(int x, int y, t_vars vars)
{
	t_data	data;
	int	size;
	//dont work properly, different image.
	size = 10 * MINIMAP_SCALE;
	data.img = mlx_new_image(vars.init, size, size);
	data.img_addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
		&data.endian);
	draw_square_on_image(&data, size, PLAYER_COLOR);
	mlx_put_image_to_window(vars.init, vars.window, data.img, x, y);
	mlx_destroy_image(vars.init, data.img);
}

void	render_player(t_all all)
{
	draw_player(all.player.x * MINIMAP_SCALE, all.player.y * MINIMAP_SCALE,
		all.vars);
	dda_draw_line(
		all.player.x * MINIMAP_SCALE,
		all.player.y * MINIMAP_SCALE,
		(all.player.x + cos(all.player.rot_angle) * 10) * MINIMAP_SCALE,
		(all.player.y + sin(all.player.rot_angle) * 10) * MINIMAP_SCALE,
		all.vars);
}
