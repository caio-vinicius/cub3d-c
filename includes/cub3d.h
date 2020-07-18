/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:29 by caio              #+#    #+#             */
/*   Updated: 2020/07/18 13:50:12 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub.h"
# include "bmp.h"

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INT_MAX 2147483647

# define M_KEYPRESS 1L << 0
# define M_KEYRELEASE 1L << 1
# define M_KEYDESTROY 1L << 17
# define E_KEYPRESS 2
# define E_KEYRELEASE 3
# define E_KEYDESTROY 17

# define PI 3.14159265
# define TWO_PI 6.28318530

# define MINIMAP_SCALE 0.25
# define MINIMAP_MARGIN 10
# define WALL_STRIP_WIDTH 1.0
# define FOV_ANGLE (60 * (PI / 180))

# define TILE_SIZE 32
# define TEX_WIDTH 32
# define TEX_HEIGHT 32

# define SOUTH (PI / 2)
# define WEST (PI)
# define NORTH (PI * 1.5)
# define EAST TWO_PI

# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define UP_ARROW 119
# define DOWN_ARROW 115
# define LEFT_ARROW 97
# define RIGHT_ARROW 100
# define ESC 65307

# define WALL_3D_COLOR 0xffffffff
# define WALL_3D_2COLOR 0xffcccccc
# define WALL_2D_COLOR 0xa6a6a6

typedef struct	s_data {
	void	*img;
	char	*img_addr;
	int	bpp;
	int	line_length;
	int	endian;
}		t_data;

typedef struct		s_vars {
	void		*init;
	void		*window;
}			t_vars;

typedef struct	s_player {
	int	x;
	int	y;
	void	*player;
	int	ad_direction; 
	int	ws_direction;
	float	rot_angle;
	float	ad_speed;
	float	ws_speed;
}		t_player;

typedef struct	s_ray {
	float	angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int	was_hit_vertical;
	int	facing_up;
	int	facing_down;
	int	facing_left;
	int	facing_right;
	int	wall_hit_content;
}		t_ray;

typedef struct	s_ray_vars {
	float	angle;
	int	facing_up;
	int	facing_down;
	int	facing_left;
	int	facing_right;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	x_to_check;
	float	y_to_check;
	int	id;
}		t_ray_vars;

typedef struct	s_grid_vars {
	int	found_wall_hit;
	float	wall_hit_x;
	float	wall_hit_y;
	int	wall_content;
	float	next_touch_x;
	float	next_touch_y;
}		t_grid_vars;

typedef struct	s_wall {
	float	perp_distance;
	float	distance_projection_plane;
	float 	projected_height;
	int	strip_height;
	int	top_pixel;
	int	bottom_pixel;
	int	texture_offset_x;
	int	texture_offset_y;
	int	distance_from_top;
}		t_wall;

typedef struct		s_sprite {
	float		x;
	float		y;
	float		invdet;
	float		transform_x;
	float		transform_y;
	int		screen_x;
	int		width;
	int		height;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
	float		*zbuffer;
	int		*order;
	float		*distance;
	int		tex_x;
	int		tex_y;
	int		d;
	float		plane_x;
	float		plane_y;
	float		dir_x;
	float		dir_y;
	float		pos_x;
	float		pos_y;
	unsigned int	amount;
	t_sprites_pos	*positions;
}			t_sprite;

typedef struct	s_img {
	void	*img;
	int	*img_addr;
	int	bpp;
	int	line_length;
	int	endian;
}		t_img;

typedef struct	s_tex {
	t_data	no;
	t_data  so;
	t_data	we;
	t_data	ea;
	t_img	s;
}		t_tex;

typedef struct		s_game {
	t_vars		vars;
	t_player	player;
	t_ray		*ray;
	t_cub		*cub;
	t_data		data;
	t_sprite	sprite;
	t_tex		textures;
	unsigned int	bmp;
}			t_game;

void	game_print_exit		(int id, int type, t_game game);
void	game_mlxpixelput	(t_data *data, int x, int y, int color);
void	game_drawline		(int x0, int y0, int x1, int y1, t_data *data);
float	game_distancepoints	(float x1, float y1, float x2, float y2);
float	game_normalizeangle	(float angle);
int	game_iswalkable		(float x, float y, char **map, t_gen gen);
void	game_drawsquare		(t_data *data, int size, int color);
void	game_castallrays	(t_game *game);
void	game_castray		(float ray_angle, int id, t_game *game);
void	game_moveplayer		(t_player *player, t_cub cub, t_sprite *sprite, char dir);
void	game_rendermap		(t_data *data, t_cub *cub);
void	game_renderrays		(t_data *data, t_cub *cub, t_player player, t_ray *ray);
void	game_renderwalls	(t_data *data, t_ray *ray, t_cub *cub, t_player player, t_tex textures, t_sprite *sprite);
void	game_renderbackground	(t_data *data, t_cub *cub);
void	game_rendersprites	(t_data *data, t_sprite sprite, t_cub *cub, t_player player, t_img texture);
void	game_validateargs	(int argc, char *argv[], t_game *game);
void	game_validatescreen	(t_vars vars, t_cub *cub);
int	game_loop		(int keycode, t_game *game);
void	bmp_save_bitmap		(t_data data, t_cub cub);

#endif
