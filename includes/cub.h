/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:22:38 by caio              #+#    #+#             */
/*   Updated: 2020/06/16 16:05:04 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define EXIT_SUCESS 0
# define EXIT_FAILURE 1

// error codes
# define EBADFD 1 /* File descriptor in bad state */
# define ENSURRW 2 /* Map no surround by walls */
# define EBADCUB 3 /* Bad cub file */
# define EMISCUB 4 /* Missing cub file */

# include "get_next_line.h"
# include "libft.h"

# include <stdio.h>

typedef struct	s_cub {
	int	width;
	int	height;
	char	*t_no;
	char	*t_so;
	char	*t_we;
	char	*t_ea;
	char	*t_s;
	char	*floor;
	char	*ceiling;
	char	**map;
	int	cols;
	int	rows;
}		t_cub;

typedef struct	s_rgb {
	char	*cr;
	char	*cg;
	char	*cb;
}		t_rgb;

t_cub	cub_analyzecub(char *file);
void	cub_getr(char *s, t_cub *cub);
char	*cub_getrgb(char *s);
char	**cub_getmap(char *s, int j);
void	cub_validatevars(t_cub cub);
void	cub_validatemap(char **map);
char	**cub_formatmap(char **map, t_cub *cub);
int	cub_isstrmap(char *s);
int	cub_ischarmap(char c);
int	cub_iswall(int c);
void	print_err_exit(int errno);
int	cub_ptrlen(char **ptr);

#endif
