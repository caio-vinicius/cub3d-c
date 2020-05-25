/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/05/25 13:48:08 by nayran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_vars *vars)
{
	vars->init = mlx_init();
	vars->window = mlx_new_window(vars->init, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");	
}

t_player	update(t_player vars)
{
	vars.x += 1;
	vars.y += 1;
	return (vars);
}

void	setup(t_player vars)
{
	//vars = malloc(sizeof(t_player));
	vars.x = 0;
	vars.y = 0;
}

void	process_keys(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->init, vars->window);
	printf("%d\n", keycode);
}

int	game_loop(int keycode, t_vars *vars)
{
	process_keys(keycode, vars);
	//update(player);
	//printf("%d %d\n", keycode, player);

	return (0);
}

int	main(void)
{
	t_vars vars;
	t_player player;

	init(&vars);
	
	setup(player);
	printf("%d - %d", player.x, player.y);
	player = update(player);
	printf("\n%d - %d", player.x, player.y);
/*
	if (vars.init && vars.window)
	{
		mlx_hook(vars.window, E_KEYPRESS, M_KEYPRESS, game_loop, &vars);
		mlx_loop_hook(vars.init, game_loop, &vars);
		mlx_loop(vars.init);
	}
*/	return (0);
}
