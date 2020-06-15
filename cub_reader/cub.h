/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:22:38 by caio              #+#    #+#             */
/*   Updated: 2020/06/15 16:01:18 by caio             ###   ########.fr       */
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

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

# include <stdio.h>

typedef struct	s_cub {
	int		width;
	int		height;
	char	*t_no;
	char	*t_so;
	char	*t_we;
	char	*t_ea;
	char	*t_s;
	char	*floor;
	char	*ceiling;
	char	**map;
	int		cols;
	int		rows;
}				t_cub;

typedef struct	s_rgb {
	char		*cr;
	char		*cg;
	char		*cb;
}				t_rgb;

void	get_resolution(char *s, t_cub *cub);
char	*get_rgb(char *s, t_cub *cub);
char	**get_map(char *s, int j);
int		is_l_map(char *s);
int		is_c_map(char c);
void	print_err_exit(int errno);

#endif
