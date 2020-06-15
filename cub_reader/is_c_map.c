/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_c_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 10:05:07 by caio              #+#    #+#             */
/*   Updated: 2020/06/15 12:13:50 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		is_c_map(char c)
{
	if (!c || c == '\0')
		return (0);
	if (c == '0' || c == '1' || c == '2' || c == 'N' ||
			c == 'S' || c == 'E' || c == 'W')
			return (1);
	else
			return (0);
}