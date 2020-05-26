/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:29 by caio              #+#    #+#             */
/*   Updated: 2020/05/26 17:39:47 by caio             ###   ########.fr       */
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

# define TILE_SIZE 42
# define MAP_NUM_ROWS 11
# define MAP_NUM_COLS 15

# define WINDOW_WIDTH (TILE_SIZE * MAP_NUM_COLS)
# define WINDOW_HEIGHT (TILE_SIZE * MAP_NUM_ROWS)

# define FOV_ANGLE (60 * (PI / 180))

# define NUM_RAYS WINDOW_WIDTH


typedef struct		s_vars {
	void		*init;
	void		*window;
}			t_vars;

typedef struct	s_data {
	void	*img;
	char	*img_addr;
	int	bpp;
	int	line_lenght;
	int	endian;
}		t_data;

typedef struct	s_player {
	int	x;
	int	y;
	void	*player;
}		t_player;

typedef struct		s_all {
	t_vars		vars;
	t_player	player;
}			t_all;

#endif
