/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/05/25 13:19:04 by caio             ###   ########.fr       */
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

void	update(t_player *player)
{
	player->x += 1;
	player->y += 1;
}

t_player	*setup()
{
	t_player *player;
	
	player.x = 0;
	player.y = 0;
	
	return (&player);
}

void	process_keys(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->init, vars->window);
	//printf("%d\n", keycode);
}

int	game_loop(int keycode, t_vars *vars)
{
	process_keys(keycode, vars);
	//update(vars);
	render();
}

int	main(void)
{
	t_vars *vars;
	t_player *player;

	init(vars);
	
	player = setup();

	if (vars->init && vars->window)
	{
		mlx_hook(vars->window, E_KEYPRESS, M_KEYPRESS, game_loop, &vars);
		mlx_loop_hook(vars->init, game_loop, &vars);
		mlx_loop(vars->init);
	}
}
