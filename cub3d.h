/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:29 by caio              #+#    #+#             */
/*   Updated: 2020/05/27 21:58:12 by caio             ###   ########.fr       */
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

typedef struct		s_all {
	t_vars		vars;
	t_player	player;
}			t_all;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	dda_draw_line(int x0, int y0, int x1, int y1, t_vars vars);

#endif
