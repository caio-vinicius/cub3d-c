/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_print_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:05:42 by caio              #+#    #+#             */
/*   Updated: 2020/06/19 15:24:07 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mem_exit_clear(t_all all)
{
	int i;

	i = 0;
	free(all.cub->t_no);
	free(all.cub->t_so);
	free(all.cub->t_we);
	free(all.cub->t_ea);
	free(all.cub->t_s);
	free(all.ray);
	while (all.cub->gen.rows > i)
	{
		free(all.cub->map[i]);
		i++;
	}
	//mlx_destroy_image(all.vars.init, all.data.img);
	//mlx_destroy_window(all.vars.init, all.vars.window);
}

void	game_print_exit(int id, int type, t_all all)
{
	if (type == 2)
	{
		if (id == EMISCUB)
			ft_putstr_fd("Usage: ./cub3D cub_file [ --save ]\n\toptions: \
				\n\t\t--save Save the first rendered image in bmp format", type);
		exit (EXIT_FAILURE);
	}
	else if (type == 1)
	{
		if (id == CLOSECL)
			ft_putstr_fd("Closing cub3D...\n", type);
		mem_exit_clear(all);
		exit (EXIT_SUCESS);
	}
}
