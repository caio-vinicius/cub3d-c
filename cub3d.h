/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:29 by caio              #+#    #+#             */
/*   Updated: 2020/05/29 13:37:53 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
// remeber to remove
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define INT_MAX 2147483647

# define M_KEYPRESS 1L<<0
# define M_KEYRELEASE 1L<<1
# define E_KEYPRESS 2
# define E_KEYRELEASE 3

# define PI 3.14159265
# define TWO_PI 6.28318530

# define TILE_SIZE 32
# define MAP_NUM_ROWS 8
# define MAP_NUM_COLS 12

# define MINIMAP_SCALE 1.0

# define WINDOW_WIDTH (TILE_SIZE * MAP_NUM_COLS)
# define WINDOW_HEIGHT (TILE_SIZE * MAP_NUM_ROWS)

# define FOV_ANGLE (60 * (PI / 180))

# define NUM_RAYS WINDOW_WIDTH

# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

extern const int map[MAP_NUM_ROWS][MAP_NUM_COLS];

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
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int	was_hit_vertical;
	int	ray_facing_up;
	int	ray_facing_down;
	int	ray_facing_left;
	int	ray_facing_right;
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

typedef struct		s_all {
	t_vars		vars;
	t_player	player;
	t_ray		ray;
}			t_all;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	dda_draw_line(int x0, int y0, int x1, int y1, t_vars vars);
float	distance_points(float x1, float y1, float x2, float y2);
float	normalize_angle(float angle);
int	is_walkable(float x, float y);
void	cast_ray(float ray_angle, int id, t_all *all);
void	draw_square_on_image(t_data *data, int size, int color);
void	render_map(t_vars vars);
void	render_player(t_all all);
void	render_rays(t_all *all);
void	move_player(t_player *player);
void	cast_all_rays(t_all *all);
int	game_loop(int keycode, t_all *all);

#endif
