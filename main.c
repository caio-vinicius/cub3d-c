/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/05/24 21:40:32 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_vars *vars)
{
	vars->init = mlx_init();
	vars->window = mlx_new_window(vars->init, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");	
}

void	render()
{
	
}

void	update(t_vars *vars)
{
	vars->x += 1;
	vars->y += 1;
}

void	setup(t_vars *vars)
{
	vars = malloc(sizeof(t_vars));
	vars->x = 0;
	vars->y = 0;
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
	//update(vars);
	render();
	//printf("%d %p\n", keycode, player);
}

int	main(void)
{
	t_vars vars;

	init(&vars);
	
	setup(&vars);

	if (vars.init && vars.window)
	{
		mlx_hook(vars.window, E_KEYPRESS, M_KEYPRESS, game_loop, &vars);
		mlx_loop_hook(vars.init, game_loop, &vars);
		mlx_loop(vars.init);
	}
}
