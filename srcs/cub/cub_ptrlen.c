/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_ptrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:20:33 by caio              #+#    #+#             */
/*   Updated: 2020/06/15 23:02:41 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	cub_ptrlen(char **ptr)
{
	int y;

	y = 0;
	while (ptr[y])
		y++;
	return (y);
}
