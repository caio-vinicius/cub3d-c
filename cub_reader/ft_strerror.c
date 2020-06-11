/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 20:24:00 by caio              #+#    #+#             */
/*   Updated: 2020/06/11 20:24:18 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_strerror(int errno)
{
	if (errno == EBADCUB)
		ft_putstr_fd("Error:\nBad cub file\n", 1);
	else if (errno == EBADFD)
		ft_putstr_fd("Error:\nFile descriptor in bad state\n", 1);
	exit (EXIT_FAILURE);
}
