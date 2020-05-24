/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:29 by caio              #+#    #+#             */
/*   Updated: 2020/05/23 20:54:28 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
// remeber to remove
# include <stdio.h>

# define M_KEYPRESS 1L<<0
# define M_KEYRELEASE 1L<<1
# define E_KEYPRESS 2
# define E_KEYRELEASE 3

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 400

typedef struct	s_vars {
	void	*init;
	void	*window;
}		t_vars;

typedef struct	s_player {
	int	x;
	int	y;
}		t_player;

typedef struct		s_all {
	t_vars		*vars;
	t_player	*player;
}			t_all;

#endif
