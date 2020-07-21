/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_validateargs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:05:06 by caio              #+#    #+#             */
/*   Updated: 2020/06/25 12:00:35 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_validateargs(int argc, char *argv[], t_game *game)
{
	game->bmp = 0;
	if (!argv[1])
		game_print_exit(EMISCUB, 2, *game);
	if (argc == 3)
	{
		if (argv[2] && ((ft_strncmp(argv[2], "--save", 5)) == 0))
			game->bmp = 1;
		else
			game_print_exit(EMISCUB, 2, *game);
	}
	if (argc > 3)
		game_print_exit(EMISCUB, 2, *game);
}
