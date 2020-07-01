/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rendersprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 21:37:49 by caio              #+#    #+#             */
/*   Updated: 2020/07/01 13:45:05 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_distance(t_game *game, t_player player)
{
	float			distance[game->sprite.amount];
	int				distance_tmp;
	int				tmp;
	unsigned int	i;

	i = 0;
	while (i < game->sprite.amount)
	{
		game->sprite.order[i] = i;
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
			game->sprite.order[i] = game->sprite.order[i + 1];
			game->sprite.order[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

static void	sprite_height(t_game *game, t_sprite *sprite)
{
	sprite->height = abs((int)(game->cub->height / sprite->transform_y));
	sprite->draw_start_y = -sprite->height / 2 + game->cub->height / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->height / 2 + game->cub->height / 2;
	if (sprite->draw_end_y >= (int)game->cub->height)
		sprite->draw_end_y = game->cub->height - 1;
}

static void	sprite_width(t_game *game, t_sprite *sprite)
{
	sprite->width = abs((int)(game->cub->height / sprite->transform_y));
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_end_x >= (int)game->cub->width)
		sprite->draw_end_x = game->cub->width - 1;
}

static void		draw_sprite(t_game *game, t_sprite *sprite, t_data *data)
{
	unsigned int color;

	color = 0;
	while (sprite->draw_start_x < sprite->draw_end_x)
	{
		sprite->tex_x = (int)(256 * (sprite->x - (-sprite->width / 2 +
						sprite->screen_x)) * TEX_WIDTH / sprite->width) / 256;
		if (sprite->transform_y > 0 && sprite->draw_start_x >= 0 &&
				sprite->draw_start_x < (int)game->cub->width && sprite->transform_y <
				sprite->zbuffer[(int)sprite->draw_start_x])
		{
			while (sprite->y < sprite->draw_end_y)
			{
				sprite->d = (sprite->y) * 256 - game->cub->height * 128
					+ sprite->height * 128;
				sprite->tex_y = ((sprite->d * TEX_HEIGHT) /
						sprite->height) / 256;
				color = game->textures.s.img_addr[(int)TEX_WIDTH *
					sprite->tex_y + sprite->tex_x];
				if (color != 0)
					data->img_addr[(int)sprite->x] = color;
				sprite->y++;
			}
		}
		sprite->x++;
	}
}

void	game_rendersprites(t_data *data, t_player player, t_game *game)
{
	t_sprite sprite;
	unsigned int i;

	sprite.dir_x = game->sprite.dir_x;
	sprite.dir_y = game->sprite.dir_y;
	sprite.plane_x = game->sprite.plane_x;
	sprite.plane_y = game->sprite.plane_y;
	sprite.pos_x = game->sprite.pos_x;
	sprite.pos_y = game->sprite.pos_y;
	i = 0;
	get_distance(game, player);
	while (i < game->sprite.amount)
	{
		sprite.x = 2.0 - sprite.pos_x;
		sprite.y = 2.0 - sprite.pos_y;
		sprite.invdet = 1.0 / (sprite.plane_x * sprite.dir_y - sprite.dir_x * sprite.plane_y);
		sprite.transform_x = sprite.invdet * (sprite.dir_y * sprite.x - sprite.dir_x * sprite.y);
		sprite.transform_y = sprite.invdet * (-sprite.plane_y * sprite.x + sprite.plane_x * game->sprite.y);
		sprite.screen_x = (int)(game->cub->width / 2) * (1 + sprite.transform_x / sprite.transform_y);
		sprite_height(game, &sprite);
		sprite_width(game, &sprite);
		draw_sprite(game, &sprite, data);
		i++;
	}
}
