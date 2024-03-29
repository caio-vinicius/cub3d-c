/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_print_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:05:42 by caio              #+#    #+#             */
/*   Updated: 2020/07/27 10:04:53 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mem_exit_clear(t_game game)
{
	int i;

	i = 0;
	free(game.cub->t_no);
	free(game.cub->t_so);
	free(game.cub->t_we);
	free(game.cub->t_ea);
	free(game.cub->t_s);
	free(game.ray);
	while (game.cub->gen.rows > i)
	{
		free(game.cub->map[i]);
		i++;
	}
	free(game.cub->map);
	free(game.cub->gen.sprites);
	free(game.cub);
}

void		game_print_exit(int id, int type, t_game game)
{
	if (type == 2)
	{
		if (id == EMISCUB)
			ft_putstr_fd("Usage: ./cub3D cub_file [ --save ]\n\toptions: \
			\n\t\t--save Save the first rendered image in bmp format", type);
		else if (id == EPATH)
			ft_putstr_fd("Error\nPath textures error\n", type);
		exit(EXIT_FAILURE);
	}
	else if (type == 1)
	{
		if (id == CLOSECL)
			ft_putstr_fd("Closing cub3D...\n", type);
		mem_exit_clear(game);
		exit(EXIT_SUCESS);
	}
}
