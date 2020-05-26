/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:00 by caio              #+#    #+#             */
/*   Updated: 2020/05/26 12:05:43 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vars	init(t_vars vars)
{
	vars.init = mlx_init();
	vars.window = mlx_new_window(vars.init, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	return (vars);
}	

void	render(t_all all)
{
	mlx_clear_window(all.vars.init, all.vars.window);
	mlx_put_image_to_window(all.vars.init, all.vars.window,
		all.player.player, all.player.x, all.player.y);
}

t_player	update(t_player player)
{
	player.x += 1;
	player.y += 1;
	return (player);
}

t_all	setup(t_all all)
{
	int width;
	int height;
	
	all.player.player = mlx_xpm_file_to_image(all.vars.init,
		"textures/stone.xpm", &width, &height);
	all.player.x = 0;
	all.player.y = 0;
	return (all);
}

void	process_keys(int keycode, t_vars vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars.init, vars.window);
}

int	game_loop(int keycode, t_all *all)
{
	//sleep(1);
	process_keys(keycode, all->vars);
	all->player = update(all->player);
	render(*all);
	printf("x %d y %d\n", all->player.x, all->player.y);
}

int	main(void)
{
	t_all all;

	all.vars = init(all.vars);	
	all = setup(all);
	game_loop(0, &all);

	if (all.vars.init && all.vars.window)
	{
		mlx_hook(all.vars.window, E_KEYPRESS, M_KEYPRESS, game_loop, &all);
		//mlx_loop_hook(all.vars.init, game_loop, &all);
		mlx_loop(all.vars.init);
	}
}
