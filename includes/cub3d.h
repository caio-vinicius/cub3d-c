/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:29 by caio              #+#    #+#             */
/*   Updated: 2020/06/16 18:16:24 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub.h"

# include <mlx.h>
# include <math.h>
// remember to remove
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INT_MAX 2147483647

# define M_KEYPRESS 1L<<0
# define M_KEYRELEASE 1L<<1
# define E_KEYPRESS 2
# define E_KEYRELEASE 3

# define PI 3.14159265
# define TWO_PI 6.28318530

# define TILE_SIZE 40
# define MAP_NUM_ROWS 12
# define MAP_NUM_COLS 16

# define MINIMAP_SCALE 0.2
//bug here when strip width is changed
# define WALL_STRIP_WIDTH 1.0

# define FOV_ANGLE (60 * (PI / 180))

# define WINDOW_WIDTH (TILE_SIZE * MAP_NUM_COLS)
# define WINDOW_HEIGHT (TILE_SIZE * MAP_NUM_ROWS)

# define NUM_RAYS WINDOW_WIDTH

# define TEX_WIDTH 32
# define TEX_HEIGHT 32

# define SOUTH (PI / 2)
# define WEST (PI)
# define NORTH (PI * 1.5)
# define EAST (PI * 2.0)

# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

# define WALL_3D_COLOR 0xffffffff
# define WALL_3D_2COLOR 0xffcccccc
# define WALL_2D_COLOR 0xa6a6a6
# define PLAYER_COLOR 0x000000
# define CEILING_COLOR 0xff333333
# define FLOOR_COLOR 0xff777777

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
}		t_ray[NUM_RAYS];

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

typedef struct		s_all {
	t_vars		vars;
	t_player	player;
	t_ray		ray;
	t_cub		cub;
}			t_all;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	dda_draw_line(int x0, int y0, int x1, int y1, t_vars vars);
float	distance_points(float x1, float y1, float x2, float y2);
float	normalize_angle(float angle);
int	is_walkable(float x, float y, char **map);
void	cast_ray(float ray_angle, int id, t_all *all);
void	draw_square_on_image(t_data *data, int size, int color);
void	render_map(t_data *data, t_cub cub);
void	render_player(t_all all);
void	render_rays(t_all *all);
void	render_walls(t_data *data, t_all all);
void	render_background(t_data *data);
void	move_player(t_player *player, t_cub cub);
void	cast_all_rays(t_all *all);
int	game_loop(int keycode, t_all *all);
int	sum_rgb(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

#endif
