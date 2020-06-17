/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validatevars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:32:01 by caio              #+#    #+#             */
/*   Updated: 2020/06/17 09:30:22 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_validatevars(t_cub cub)
{
	if (!cub.width || !cub.height)
		print_exit(EBADCUB, 2);
	else if (!cub.t_no || !cub.t_so || !cub.t_we || !cub.t_ea || !cub.t_s)
		print_exit(EBADCUB, 2);
	else if (!cub.floor || !cub.ceiling)
		print_exit(EBADCUB, 2);
	else if (!cub.map[0])
		print_exit(EBADCUB, 2);
	else if (!cub.gen.rot_angle)
		print_exit(EBADCUB, 2);
}
