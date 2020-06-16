/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 20:24:00 by caio              #+#    #+#             */
/*   Updated: 2020/06/15 22:50:25 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_err_exit(int errno)
{
	if (errno == EBADCUB)
		ft_putstr_fd("Error\nBad cub file\n", 1);
	else if (errno == EBADFD)
		ft_putstr_fd("Error\nFile descriptor in bad state\n", 1);
	else if (errno == ENSURRW)
		ft_putstr_fd("Error\nMap not surround by walls", 1);
	else if (errno == EMISCUB)
		ft_putstr_fd("Error\nUsage: ./cub3D cub_file [ --save ]\n\toptions: \
				\n\t\t--save Save the first rendered image in bmp format", 1);
	exit (EXIT_FAILURE);
}
