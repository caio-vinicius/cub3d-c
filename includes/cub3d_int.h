/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:29 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 20:25:37 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_INT_H
# define CUB3D_INT_H

# define INT_MAX 2147483647

# define EKEYPRESS 2
# define EKEYRELEASE 3
# define EKEYDESTROY 17

# define PI 3.14159265
# define TWO_PI 6.28318530

# define MINIMAP_SCALE 0.25
# define MINIMAP_MARGIN 10
# define WALL_STRIP_WIDTH 1.0

# define TILE_SIZE 32
# define TEX_WIDTH 32
# define TEX_HEIGHT 32

# define WALL_3D_COLOR 0xffffffff
# define WALL_3D_2COLOR 0xffcccccc
# define WALL_2D_COLOR 0xa6a6a6

typedef struct		s_draw_line {
	int				x0;
	int				y0;
	int				x1;
	int				y1;
}					t_draw_line;

typedef struct		s_ray_vars {
	float			angle;
	int				facing_up;
	int				facing_down;
	int				facing_left;
	int				facing_right;
	float			xintercept;
	float			yintercept;
	float			xstep;
	float			ystep;
	float			x_to_check;
	float			y_to_check;
	int				id;
}					t_ray_vars;

typedef struct		s_grid_vars {
	int				found_wall_hit;
	float			wall_hit_x;
	float			wall_hit_y;
	int				wall_content;
	float			next_touch_x;
	float			next_touch_y;
}					t_grid_vars;

typedef struct		s_wall {
	float			perp_distance;
	float			distance_projection_plane;
	int				strip_height;
	int				top_pixel;
	int				bottom_pixel;
	int				texture_offset_x;
	int				texture_offset_y;
	int				distance_from_top;
}					t_wall;

typedef struct		s_vars {
	void			*init;
	void			*window;
}					t_vars;

typedef struct		s_player {
	int				x;
	int				y;
	float			fov;
	int				ad_direction;
	int				ws_direction;
	float			rot_angle;
	float			ad_speed;
	float			ws_speed;
}					t_player;

typedef struct		s_ray {
	float			angle;
	float			wall_hit_x;
	float			wall_hit_y;
	float			distance;
	int				was_hit_vertical;
	int				facing_up;
	int				facing_down;
	int				facing_left;
	int				facing_right;
	int				wall_hit_content;
}					t_ray;

typedef struct		s_data {
	void			*img;
	char			*img_addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_data;

typedef struct		s_img {
	void			*img;
	int				*img_addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct		s_tex {
	t_data			no;
	t_data			so;
	t_data			we;
	t_data			ea;
	t_img			s;
}					t_tex;

typedef struct		s_sprite {
	float			x;
	float			y;
	float			invdet;
	float			transform_x;
	float			transform_y;
	int				screen_x;
	int				width;
	int				height;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	float			*zbuffer;
	int				*order;
	float			*distance;
	int				tex_x;
	int				tex_y;
	int				d;
	float			plane_x;
	float			plane_y;
	float			dir_x;
	float			dir_y;
	float			pos_x;
	float			pos_y;
	t_img			texture;
	unsigned int	amount;
	t_sprites_pos	*positions;
}					t_sprite;

void				init_horz_vert			(t_grid_vars *vars);
void				set_ray_vert			(t_ray *ray, t_grid_vars vert,
												float vert_hit, int id);
void				set_ray_horz			(t_ray *ray, t_grid_vars horz,
												float horz_hit, int id);
void				define_dir_plane		(char pos, t_sprite *sprite);
float				define_dir				(char rot_angle);
t_ray_vars			find_coords_to_check	(t_ray_vars ray, t_grid_vars *vars,
												int time);

#endif
