/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 20:24:00 by caio              #+#    #+#             */
/*   Updated: 2020/06/17 09:26:49 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_exit(int id, int type)
{
	if (type == 2)
	{
		if (id == EBADCUB)
			ft_putstr_fd("Error\nBad cub file\n", type);
		else if (id == EBADFD)
			ft_putstr_fd("Error\nFile descriptor in bad state\n", type);
		else if (id == ENSURRW)
			ft_putstr_fd("Error\nMap not surround by walls", type);
		else if (id == EMISCUB)
			ft_putstr_fd("Usage: ./cub3D cub_file [ --save ]\n\toptions: \
				\n\t\t--save Save the first rendered image in bmp format", type);
		exit (EXIT_FAILURE);
	}
	else if (type == 1)
	{
		if (id == CLOSECL)
			ft_putstr_fd("Closing cub3D...\n", type);
		exit (EXIT_SUCESS);
	}
}
