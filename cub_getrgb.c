/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_getrgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 23:33:27 by caio              #+#    #+#             */
/*   Updated: 2020/06/18 12:02:04 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	mem_clear(char **color, t_rgb value)
{
	free(color);
	free(color[0]);
	free(color[1]);
	free(color[2]);
	free(value.r);
	free(value.g);
	free(value.b);
}

char	*cat_rgb(char *r, char *g, char *b)
{
	int		length;
	char	*str;

	length = ft_strlen(r) + ft_strlen(g) + ft_strlen(b);
	str = malloc(length + 1);
	if (str)
	{
		ft_strlcpy(str, r, length);
		ft_strlcat(str, g, length);
		ft_strlcat(str, b, length);
	}
	return (str);
}

char	*cub_getrgb(char *s)
{
	t_rgb	value;
	char	*rgb;
	char	**color;
	int		i;

	i = 0;
	color = ft_split(s, ',');
	value.r = ft_itoa_base(ft_atoi(color[0]), 16);
	value.g = ft_itoa_base(ft_atoi(color[1]), 16);
	value.b = ft_itoa_base(ft_atoi(color[2]), 16);
	rgb = cat_rgb(value.r, value.g, value.b);
	mem_clear(color, value);
	//remember to free rgb after
	return (rgb);
}
