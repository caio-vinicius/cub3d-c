/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/05/23 21:10:22 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

t_vars	*init(t_vars *vars)
{
	vars->init = mlx_init();
	vars->window = mlx_new_window(vars->init, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (vars->init && vars->window)
		return (vars);
	return (NULL);
}

void	render()
{
	
}

void	update(t_player *player)
{
	player->x += 1;
	player->y += 1;
}

void	setup(t_player *player)
{
	player->x = 0;
	player->y = 0;
}

void	process_keys(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->init, vars->window);
	printf("%d\n", keycode);
}

int	game_loop(int keycode, t_all *all)
{
	//sleep(1);
	process_keys(keycode, all->vars);
	update(all->player);
	render();
}

int	main(void)
{
	t_all *all;
	t_vars *vars; 

	vars = init(vars);
	all->vars = vars;

	setup(all->player);

	if (all->vars)
	{
		mlx_hook(all->vars->window, E_KEYPRESS, M_KEYPRESS, game_loop, &all);
		//mlx_loop_hook(vars->init, game_loop, &all);
		mlx_loop(all->vars->init);
	}
}
