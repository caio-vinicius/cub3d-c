/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_print_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 20:24:00 by caio              #+#    #+#             */
/*   Updated: 2020/06/20 15:47:48 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_print_exit(int id)
{
	if (id == EBADCUB)
		ft_putstr_fd("Error\nBad cub file\n", 2);
	else if (id == EBADFD)
		ft_putstr_fd("Error\nFile descriptor in bad state\n", 2);
	else if (id == ENSURRW)
		ft_putstr_fd("Error\nMap not surround by walls", 2);
	else if (id == EMISCUB)
		ft_putstr_fd("Usage: ./cub3D cub_file [ --save ]\n\toptions: \
			\n\t\t--save Save the first rendered image in bmp format", 2);
	else if (id == EMDIR)
		ft_putstr_fd("Error\nMissing position letter on map\n", 2);
	exit (EXIT_FAILURE);
}
