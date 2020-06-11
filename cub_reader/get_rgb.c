/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 23:33:27 by caio              #+#    #+#             */
/*   Updated: 2020/06/10 23:35:52 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_rgb_digit(char *s, char *color, int i)
{
	int j;

	j = 0;
	while (ft_isdigit(s[i]))
		color[j++] = s[i++];
	i++;
	color[i] = '\0';
	return (i);
}


//sure memory leak here, check later
char	*get_rgb(char *s, t_cub *cub)
{
	t_rgb	rgb;
	char	*color;
	int		i;

	i = 0;
	if (((rgb.cr = (char*)ft_calloc(4, sizeof(char))) &&
		(rgb.cg = (char*)ft_calloc(4, sizeof(char))) &&
		(rgb.cb = (char*)ft_calloc(4, sizeof(char)))))
	{
		i = get_rgb_digit(s, rgb.cr, i);
		i = get_rgb_digit(s, rgb.cg, i);
		i = get_rgb_digit(s, rgb.cb, i);
	}
	rgb.cr = ft_itoa_base(ft_atoi(rgb.cr), 16);
	rgb.cg = ft_itoa_base(ft_atoi(rgb.cg), 16);
	rgb.cb = ft_itoa_base(ft_atoi(rgb.cb), 16);
	color = ft_strjoin(rgb.cr, rgb.cg);
	color = ft_strjoin(color, rgb.cb);
	return (color);
}
