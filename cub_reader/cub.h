/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:22:38 by caio              #+#    #+#             */
/*   Updated: 2020/06/10 23:35:58 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

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
}		t_cub;

typedef struct	s_rgb {
	char		*cr;
	char		*cg;
	char		*cb;
}				t_rgb;

void	get_resolution(char *s, t_cub *cub);
char	*get_rgb(char *s, t_cub *cub);

#endif
