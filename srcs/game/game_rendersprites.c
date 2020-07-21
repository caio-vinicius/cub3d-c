/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rendersprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 21:37:49 by caio              #+#    #+#             */
/*   Updated: 2020/07/20 16:23:39 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_sprite(t_cub cub, t_sprite *sprite, t_data *data, t_img t)
{
	unsigned int	color;
	int				x;
	int				y;

	x = sprite->draw_start_x;
	while (x < sprite->draw_end_x)
	{
		if (sprite->transform_y > 0 && x >= 0 && x < (int)cub.width &&
				sprite->transform_y < sprite->zbuffer[x])
		{
			sprite->tex_x = (int)(256 * (x - (-sprite->width / 2 +
					sprite->screen_x)) * TEX_WIDTH / sprite->width) / 256;
			y = sprite->draw_start_y;
			while (y < sprite->draw_end_y)
			{
				sprite->d = y * 256 - cub.height * 128 + sprite->height * 128;
				sprite->tex_y = (sprite->d * TEX_HEIGHT / sprite->height) / 256;
				color = t.img_addr[TEX_WIDTH * sprite->tex_y + sprite->tex_x];
				if (color << 24 != 0)
					game_mlxpixelput(data, x, y, color);
				y++;
			}
		}
		x++;
	}
}

static void	sprite_size(t_cub cub, t_sprite *sprite)
{
	sprite->height = abs((int)(cub.width / sprite->transform_y));
	sprite->draw_start_y = -sprite->height / 2 + cub.height / 2;
	sprite->draw_end_y = sprite->height / 2 + cub.height / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	if (sprite->draw_end_y >= (int)cub.height)
		sprite->draw_end_y = cub.height;
	sprite->width = abs((int)(cub.width / sprite->transform_y));
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	if (sprite->draw_end_x >= (int)cub.width)
		sprite->draw_end_x = cub.width;
}

static void	distance_sprites(t_sprite *sprite, t_player player)
{
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
}

static void	sort_sprites(t_sprite *sprite)
{
	unsigned int	i;
	int				distance_tmp;
	int				tmp;

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

void		game_rendersprites(t_data *data, t_sprite s, t_cub cub, t_player p)
{
	unsigned int i;

	i = 0;
	distance_sprites(&s, p);
	sort_sprites(&s);
	s.invdet = 1.0 / (s.plane_x * s.dir_y - s.dir_x * s.plane_y);
	while (i < s.amount)
	{
		s.x = ((float)(s.positions[i].x * TILE_SIZE + (TILE_SIZE / 2)) -
				p.x) / TILE_SIZE;
		s.y = ((float)(s.positions[i].y * TILE_SIZE + (TILE_SIZE / 2)) -
				p.y) / TILE_SIZE;
		s.transform_x = s.invdet * (s.dir_y * s.x - s.dir_x * s.y);
		s.transform_y = s.invdet * (-s.plane_y * s.x + s.plane_x * s.y);
		s.screen_x = (int)((cub.width / 2) *
				(1 + s.transform_x / s.transform_y));
		sprite_size(cub, &s);
		draw_sprite(cub, &s, data, s.texture);
		i++;
	}
}
