/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 20:24:00 by caio              #+#    #+#             */
/*   Updated: 2020/06/12 18:32:32 by caio             ###   ########.fr       */
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
		ft_putstr_fd("Error\nMap no surround by walls", 1);
	exit (EXIT_FAILURE);
}
