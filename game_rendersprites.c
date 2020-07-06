/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rendersprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 21:37:49 by caio              #+#    #+#             */
/*   Updated: 2020/07/06 14:00:03 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	get_distance(t_sprite *sprite, t_player player)
{
	float			distance[game->sprite.amount];
	int				distance_tmp;
	int				tmp;
	unsigned int	i;

	i = 0;
	while (i < sprite.amount)
	{
		sprite.order[i] = i;
		distance[i] = ((player.x - 2.0) * (player.x - 2.0) + (player.y - 2.0) * (player.y - 2.0));
		i++;
	}
	i = 0;
	while (i < game->sprite.amount)
	{
		if (distance[i] < distance[i + 1])
		{
			distance_tmp = distance[i];
			distance[i] = distance[i + 1];
			distance[i + 1] = distance_tmp;
			tmp = game->sprite.order[i];
			sprite.order[i] = sprite.order[i + 1];
			sprite.order[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}*/

static void	sprite_height(t_cub *cub, t_sprite *sprite)
{
	sprite->height = abs((int)(cub->height / sprite->transform_y));
	sprite->draw_start_y = -sprite->height / 2 + cub->height / 2;
	sprite->draw_end_y = sprite->height / 2 + cub->height / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	if (sprite->draw_end_y >= (int)cub->height)
		sprite->draw_end_y = cub->height - 1;
}

static void	sprite_width(t_cub *cub, t_sprite *sprite)
{
	sprite->width = abs((int)(cub->height / sprite->transform_y));
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	if (sprite->draw_end_x >= (int)cub->width)
		sprite->draw_end_x = cub->width - 1;
}

static void		draw_sprite(t_cub *cub, t_sprite *sprite, t_data *data, t_img texture)
{
	int color;
	int x;
	int y;

	color = 0;
	x = sprite->draw_start_x;
	y = 0;
	while (x < sprite->draw_end_x)
	{
		if (sprite->transform_y > 0 && x >= 0 && x < (int)cub->width &&
				sprite->transform_y < sprite->zbuffer[x])
		{
			sprite->tex_x = (int)(256 * (x - (-sprite->width / 2 + sprite->screen_x)) * TEX_WIDTH / sprite->width) / 256;
			y = sprite->draw_start_y - 1;
			while (++y < sprite->draw_end_y)
			{
				sprite->d = y * 256 - cub->height * 128 + sprite->height * 128;
				sprite->tex_y = ((sprite->d * TEX_HEIGHT) / sprite->height) / 256;
				color = texture.img_addr[TEX_WIDTH * sprite->tex_y + sprite->tex_x];
				if ((color & 0x00FFFFFF) != 0x0)
					data->img_addr[y * cub->width + x] = color;
			}
		}
		x++;
	}
}

void	game_rendersprites(t_data *data, t_sprite sprite, t_cub *cub, t_img texture)
{
	unsigned int i;

	i = 0;
	//get_distance(&sprite, player);
	//while (i < sprite.amount)
	//{
	sprite.x = 10.5 - sprite.pos_x;
	sprite.y = 6.5 - sprite.pos_y;
	sprite.invdet = 1.0 / (sprite.plane_x * sprite.dir_y - sprite.dir_x * sprite.plane_y);
	sprite.transform_x = sprite.invdet * (sprite.dir_y * sprite.x - sprite.dir_x * sprite.y);
	sprite.transform_y = sprite.invdet * (-sprite.plane_y * sprite.x + sprite.plane_x * sprite.y);
	sprite.screen_x = (int)((cub->width / 2) * (1 + sprite.transform_x / sprite.transform_y));
	sprite_height(cub, &sprite);
	sprite_width(cub, &sprite);
	draw_sprite(cub, &sprite, data, texture);
	//i++;
	//}
}
