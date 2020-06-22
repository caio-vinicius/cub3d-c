/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:29 by caio              #+#    #+#             */
/*   Updated: 2020/06/22 10:57:13 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub.h"
# include "bmp.h"

# include <mlx.h>
# include <math.h>
// remember to remove
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INT_MAX 2147483647

# define M_KEYPRESS 1L << 0
# define M_KEYRELEASE 1L << 1
# define E_KEYPRESS 2
# define E_KEYRELEASE 3

# define PI 3.14159265
# define TWO_PI 6.28318530

// tile size 32 and scale of 0.25 is the best combination so far
# define TILE_SIZE 32
# define MINIMAP_SCALE 0.25
# define MINIMAP_MARGIN 10
//bug here when strip width is changed
# define WALL_STRIP_WIDTH 1.0
# define FOV_ANGLE (60 * (PI / 180))

# define TEX_WIDTH 32
# define TEX_HEIGHT 32

# define SOUTH (PI / 2)
# define WEST (PI)
# define NORTH (PI * 1.5)
# define EAST (PI * 2.0)

# define UP_ARROW 119
# define DOWN_ARROW 115
# define LEFT_ARROW 97
# define RIGHT_ARROW 100
# define ESC 65307

# define WALL_3D_COLOR 0xffffffff
# define WALL_3D_2COLOR 0xffcccccc
# define WALL_2D_COLOR 0xa6a6a6
# define PLAYER_COLOR 0x000000

typedef struct		s_vars {
	void		*init;
	void		*window;
}			t_vars;

typedef struct	s_data {
	void	*img;
	char	*img_addr;
	int	bpp;
	int	line_length;
	int	endian;
}		t_data;

typedef struct	s_player {
	float	x;
	float	y;
	void	*player;
	int	ad_direction; // -1 left, +1 right
	int	ws_direction; // -1 back, +1 front
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

typedef struct		s_game {
	t_vars		vars;
	t_player	player;
	t_ray		*ray;
	t_cub		*cub;
	t_data		data;
}			t_game;

void	game_print_exit		(int id, int type, t_game game);
void	game_mlxpixelput	(t_data *data, int x, int y, int color);
void	game_drawline		(int x0, int y0, int x1, int y1, t_vars vars);
float	game_distancepoints	(float x1, float y1, float x2, float y2);
float	game_normalizeangle	(float angle);
int	game_iswalkable		(float x, float y, char **map, t_gen gen);
void	game_drawsquare		(t_data *data, int size, int color);
void	game_castallrays	(t_game *game);
void	game_castray		(float ray_angle, int id, t_game *game);
void	game_moveplayer		(t_player *player, t_cub cub);
void	game_rendermap		(t_data *data, t_cub *cub);
void	game_renderplayer	(t_player player, t_vars vars);
void	game_renderrays		(t_cub *cub, t_player player, t_ray *ray, t_vars vars);
void	game_renderwalls	(t_data *data, t_ray *ray, t_cub *cub, t_player player);
void	game_renderbackground	(t_data *data, t_cub *cub);
int	game_loop		(int keycode, t_game *game);

#endif
