/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:29 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 20:00:18 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "errno.h"
# include "cub.h"
# include "cub3d_int.h"

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define UP_ARROW 119
# define DOWN_ARROW 115
# define LEFT_ARROW 97
# define RIGHT_ARROW 100
# define ESC 65307

typedef struct		s_game {
	t_vars			vars;
	t_player		player;
	t_ray			*ray;
	t_cub			*cub;
	t_data			data;
	t_sprite		sprite;
	t_tex			textures;
	unsigned int	bmp;
}					t_game;

void				game_print_exit			(int id, int type, t_game game);
void				game_mlxpixelput		(t_data *data, int x, int y,
												int color);
void				game_drawline			(t_draw_line vars, t_data *data);
float				game_distancepoints		(float x1, float y1, float x2,
												float y2);
float				game_normalizeangle		(float angle);
int					game_iswalkable			(float x, float y, char **map,
												t_gen gen);
void				game_castallrays		(t_game *game);
void				game_castray			(float ray_angle, int id,
												t_game *game);
void				game_moveplayer			(t_player *player, t_cub cub,
												t_sprite *sprite);
void				game_rendermap			(t_data *data, t_cub *cub);
void				game_renderrays			(t_data *data, t_cub *cub,
												t_player player, t_ray *ray);
void				game_renderwalls		(t_game *game);
void				game_renderbackground	(t_data *data, t_cub *cub);
void				game_rendersprites		(t_data *data, t_sprite sprite,
												t_cub cub, t_player player);
void				game_validateargs		(int argc, char *argv[],
												t_game *game);
void				game_validatescreen		(t_vars vars, t_cub *cub);
int					game_loop				(int keycode, t_game *game);
int				game_call_loop			(t_game *game);
int				game_x_exit			(t_game *game);

void				bmp_save			(t_data data, t_cub cub);

#endif
