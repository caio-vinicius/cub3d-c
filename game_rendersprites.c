/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rendersprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 21:37:49 by caio              #+#    #+#             */
/*   Updated: 2020/07/18 14:02:07 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_sprite(t_cub *cub, t_sprite *sprite, t_data *data, t_img texture)
{
	unsigned int color;
	int x;
	int y;

	color = 0;
	x = sprite->draw_start_x;
	y = 0;
	while (x < sprite->draw_end_x)
	{
		if (sprite->transform_y > 0 && x >= 0 && x < (int)cub->width && sprite->transform_y < sprite->zbuffer[x])
		{
			sprite->tex_x = (int)(256 * (x - (-sprite->width / 2 + sprite->screen_x)) * TEX_WIDTH / sprite->width) / 256;
			y = sprite->draw_start_y;
			while (y < sprite->draw_end_y)
			{
				sprite->d = (y) * 256 - cub->height * 128 + sprite->height * 128;
				sprite->tex_y = ((sprite->d * TEX_HEIGHT) / sprite->height) / 256;
				color = texture.img_addr[TEX_WIDTH * sprite->tex_y + sprite->tex_x];
				if (color << 24 != 0)
					game_mlxpixelput(data, x, y, color);
				y++;
			}
		}
		x++;
	}
}

static void	sprite_height(t_cub *cub, t_sprite *sprite)
{
	sprite->height = abs((int)(cub->width / sprite->transform_y));
	sprite->draw_start_y = -sprite->height / 2 + cub->height / 2;
	sprite->draw_end_y = sprite->height / 2 + cub->height / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	if (sprite->draw_end_y >= (int)cub->height)
		sprite->draw_end_y = cub->height;
}

static void	sprite_width(t_cub *cub, t_sprite *sprite)
{
	sprite->width = abs((int)(cub->width / sprite->transform_y));
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen_x;
	//printf("draw_start_x %d draw_end_x %d\n", sprite->draw_start_x, sprite->draw_end_x);
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	if (sprite->draw_end_x >= (int)cub->width)
		sprite->draw_end_x = cub->width;
}

void	get_distance(t_sprite *sprite, t_player player)
{
	int				distance_tmp;
	int				tmp;
	unsigned int	i;
	int				player_x;
	int				player_y;

	player_x = player.x / TILE_SIZE;
	player_y = player.y / TILE_SIZE;
	i = 0;
	while (i < sprite->amount)
	{
		sprite->order[i] = i;
		sprite->distance[i] = pow(player_x - sprite->positions[i].x, 2) *
			pow(player_y - sprite->positions[i].y, 2);
		i++;
	}
	i = 0;
	while (i < sprite->amount)
	{
		if (sprite->distance[i] < sprite->distance[i + 1])
		{
			distance_tmp = sprite->distance[i];
			sprite->distance[i] = sprite->distance[i + 1];
			sprite->distance[i + 1] = distance_tmp;
			tmp = sprite->order[i];
			sprite->order[i] = sprite->order[i + 1];
			sprite->order[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

void	game_rendersprites(t_data *data, t_sprite sprite, t_cub *cub, t_player player, t_img texture)
{
	unsigned int i;

	i = 0;
	get_distance(&sprite, player);
	sprite.invdet = 1.0 / (sprite.plane_x * sprite.dir_y - sprite.dir_x * sprite.plane_y);
	while (i < sprite.amount)
	{
		sprite.x = ((float)(sprite.positions[i].x * TILE_SIZE + (TILE_SIZE / 2)) - player.x) / TILE_SIZE;
		sprite.y = ((float)(sprite.positions[i].y * TILE_SIZE + (TILE_SIZE / 2)) - player.y) / TILE_SIZE;
		sprite.transform_x = sprite.invdet * (sprite.dir_y * sprite.x - sprite.dir_x * sprite.y);
		sprite.transform_y = sprite.invdet * (-sprite.plane_y * sprite.x + sprite.plane_x * sprite.y);
		sprite.screen_x = (int)((cub->width / 2) * (1 + -sprite.transform_x / sprite.transform_y));
		sprite_height(cub, &sprite);
		sprite_width(cub, &sprite);
		draw_sprite(cub, &sprite, data, texture);
		i++;
	}
}
