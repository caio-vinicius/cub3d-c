/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_getr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 23:33:52 by caio              #+#    #+#             */
/*   Updated: 2020/06/18 14:32:57 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_getr(char *s, t_cub *cub)
{
	int i;
	int j;
	char *width;
	char *height;

	i = 0;
	i = ft_digitlen(s);
	width = ft_substr(s, 0, i);
	if (ft_isspace(s[i]))
		i++;
	j = i;
	i = ft_digitlen(&s[i]);
	height = ft_substr(s, j, i);
	cub->width = ft_atoi(width);
	cub->height = ft_atoi(height);
	free(width);
	free(height);
}
