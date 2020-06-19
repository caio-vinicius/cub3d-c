/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validatevars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:32:01 by caio              #+#    #+#             */
/*   Updated: 2020/06/18 17:27:05 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_validatevars(t_cub cub)
{
	if (!cub.width || !cub.height)
		cub_print_exit(EBADCUB);
	else if (!cub.t_no || !cub.t_so || !cub.t_we || !cub.t_ea || !cub.t_s)
		cub_print_exit(EBADCUB);
	else if (!cub.floor || !cub.ceiling)
		cub_print_exit(EBADCUB);
	else if (!cub.map[0])
		cub_print_exit(EBADCUB);
	else if (!cub.gen.rot_angle)
		cub_print_exit(EBADCUB);
}
