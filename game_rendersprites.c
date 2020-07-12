/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rendersprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 21:37:49 by caio              #+#    #+#             */
/*   Updated: 2020/07/12 16:23:16 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	distance(float x, float y, float xend, float yend)
{
	return (sqrt((xend - x) * (xend - x) + (yend - y) * (yend - y)));
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
		sprite->distance[i] = ((player_x - sprite->positions[i].x) * (player_x - sprite->positions[i].x) + (player_y - sprite->positions[i].y) * (player_y - sprite->positions[i].y));
		//sprite->distance[i] = distance(player_x, player_y, sprite->positions[i].x, sprite->positions[i].y);
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

static int	sprite_on_fov(t_sprite sprite, t_player player, int i)
{
	float vect_x;
	float vect_y;
	float player_to_sprite_angle;
	float sprite_angle;
	float player_angle;

	vect_x = sprite.positions[i].x - player.x / TILE_SIZE;
	vect_y = sprite.positions[i].y - player.y / TILE_SIZE;
	player_to_sprite_angle = atan2(vect_x, vect_y);
	player_angle = game_normalizeangle(player.rot_angle);
	sprite_angle = player_angle - player_to_sprite_angle;
	if (sprite_angle < PI)
		sprite_angle += TWO_PI;
	if (sprite_angle > PI)
		sprite_angle -= TWO_PI;
	sprite_angle = fabs(sprite_angle);
	if (sprite_angle < (FOV_ANGLE / 2))
		return (1);
	else
		return (0);
}

static void	sprite_height(t_cub *cub, t_sprite *sprite, int i)
{
	//sprite->height = abs((int)(cub->height / sprite->transform_y));
	float distance_projection;
	distance_projection = ((cub->width / 2) / tan(FOV_ANGLE / 2));
	sprite->height = (TILE_SIZE * 0.5 / sprite->distance[i]) * distance_projection;
	sprite->draw_start_y = -sprite->height / 2 + cub->height / 2;
	sprite->draw_end_y = sprite->height / 2 + cub->height / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	if (sprite->draw_end_y >= (int)cub->height)
		sprite->draw_end_y = cub->height - 1;
}

static void	sprite_width(t_cub *cub, t_sprite *sprite, int i)
{
	//sprite->width = abs((int)(cub->height / sprite->transform_y));
	float distance_projection;
	distance_projection = ((cub->width / 2) / tan(FOV_ANGLE / 2));
	sprite->width = (TILE_SIZE * 0.5 / sprite->distance[i]) * distance_projection;
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	if (sprite->draw_end_x >= (int)cub->width)
		sprite->draw_end_x = cub->width - 1;
}

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
		if (sprite->transform_y > 0 && x >= 0 &&
				x < (int)cub->width && sprite->transform_y < sprite->zbuffer[x])
		{
			y = sprite->draw_start_y;
			while (y < sprite->draw_end_y)
			{
				sprite->tex_x = (int)(256 * (x - (-sprite->width / 2 + sprite->screen_x)) * TEX_WIDTH / sprite->width) / 256;
				sprite->d = (y) * 256 - cub->height * 128 + sprite->height * 128;
				sprite->tex_y = ((sprite->d * TEX_HEIGHT) / sprite->height) / 256;
				color = texture.img_addr[TEX_WIDTH * sprite->tex_y + sprite->tex_x];
				if (color << 24 != 0x00)
					data->img_addr[y * cub->width + x] = color;
				y++;
			}
		}
		x++;
	}
}

void	game_rendersprites(t_data *data, t_sprite sprite, t_cub *cub, t_player player, t_img texture, t_vars vars)
{
	unsigned int i;

	i = 0;
	get_distance(&sprite, player);
	while (i < sprite.amount)
	{
		//if (sprite_on_fov(sprite, player, i))
		//{
		sprite.x = (sprite.positions[i].x + 0.5) - (player.x / TILE_SIZE);
		sprite.y = (sprite.positions[i].y + 0.5) - (player.y / TILE_SIZE);
		sprite.invdet = 1.0 / (sprite.plane_x * sprite.dir_y - sprite.dir_x * sprite.plane_y);
		sprite.transform_x = sprite.invdet * (sprite.dir_y * sprite.x - sprite.dir_x * sprite.y);
		sprite.transform_y = sprite.invdet * (-sprite.plane_y * sprite.x + sprite.plane_x * sprite.y);
		//maybe transform_x is negative here
		sprite.screen_x = (int)((cub->width / 2) * (1 + -sprite.transform_x / sprite.transform_y));
		sprite_height(cub, &sprite, i);
		sprite_width(cub, &sprite, i);
		draw_sprite(cub, &sprite, data, texture);
		mlx_put_image_to_window(vars.init, vars.window, data->img, 0, 0);
		//}
		i++;
	}
}
