/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_getr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 23:33:52 by caio              #+#    #+#             */
/*   Updated: 2020/06/19 17:32:53 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_getr(char *s, t_cub *cub)
{
	char **resolution;

	resolution = ft_split(&s[2], ' ');
	cub->width = ft_atoi(resolution[0]);
	cub->height = ft_atoi(resolution[1]);
	free(resolution[0]);
	free(resolution[1]);
	free(resolution);
}
