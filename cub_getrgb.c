/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_getrgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 23:33:27 by caio              #+#    #+#             */
/*   Updated: 2020/06/20 12:43:50 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//thank you aroque.
t_color	cub_getrgb(char *s)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	t_color			rgb;
	char			**color;

	color = ft_split(&s[2], ',');
	r = (unsigned char)ft_atoi(color[0]);
	g = (unsigned char)ft_atoi(color[1]);
	b = (unsigned char)ft_atoi(color[2]);
	rgb = (((r) << 24) + ((g) << 16) + ((b) << 8) + (0x0));
	free(color[0]);
	free(color[1]);
	free(color[2]);
	free(color);
	return (rgb);
}
