/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:22:38 by caio              #+#    #+#             */
/*   Updated: 2020/07/21 19:22:37 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define EXIT_SUCESS 0
# define EXIT_FAILURE 1

# include "errno.h"
# include "get_next_line.h"
# include "libft.h"

typedef int			t_color;

typedef struct		s_sprites_pos {
	unsigned int	x;
	unsigned int	y;
}					t_sprites_pos;

typedef struct		s_gen {
	int				cols;
	int				rows;
	int				window_width;
	int				window_height;
	int				x_player;
	int				y_player;
	char			rot_angle;
	unsigned int	amount_sprites;
	t_sprites_pos	*sprites;
}					t_gen;

typedef struct		s_cub {
	unsigned int	width;
	unsigned int	height;
	char			*t_no;
	char			*t_so;
	char			*t_we;
	char			*t_ea;
	char			*t_s;
	t_color			floor;
	t_color			ceiling;
	char			**map;
	t_gen			gen;
}					t_cub;

t_cub				*cub_analyzecub		(char *file);
void				cub_getr			(char *s, t_cub *cub);
char				*cub_getpath		(char *s, int pos);
t_color				cub_getrgb			(char *s);
char				**cub_getmap		(char *s);
void				cub_validatevars	(t_cub cub);
void				cub_validatemap		(char **map);
char				**cub_formatmap		(char **map, t_gen *gen);
void				cub_getsprites		(char **map, t_gen *gen);
int					cub_isstrmap		(char *s);
int					cub_ischarmap		(char c);
int					cub_iswall			(int c);
int					cub_ptrlen			(char **ptr);
void				cub_print_exit		(int id);

#endif
