/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_analyzecub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:27:39 by caio              #+#    #+#             */
/*   Updated: 2020/06/18 14:36:18 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	recognize_identifier(char *s, t_cub *cub)
{
	static int j;

	if (s[0] == 'R')
		cub_getr(&s[2], cub);
	else if (s[0] == 'N' && s[1] == 'O')
		cub->t_no = cub_getpath(s, 3);
	else if (s[0] == 'S' && s[1] == 'O')
		cub->t_so = cub_getpath(s, 3);
	else if (s[0] == 'W' && s[1] == 'E')
		cub->t_we = cub_getpath(s, 3);
	else if (s[0] == 'E' && s[1] == 'A')
		cub->t_ea = cub_getpath(s, 3);
	else if (s[0] == 'S')
		cub->t_s = cub_getpath(s, 2);
	else if (s[0] == 'F')
		cub->floor = cub_getrgb(&s[2]);
	else if (s[0] == 'C')
		cub->ceiling = cub_getrgb(&s[2]);
	else if (cub_isstrmap(s))
		cub->map = cub_getmap(s, j++);
	else if (s[0] == '\0')
		free(s);
	else
		print_exit(EBADCUB, 2);
	return (j);
}

void	init_cub(t_cub *cub)
{
	cub->width = 0;
	cub->height = 0;
	cub->t_no = NULL;
	cub->t_so = NULL;
	cub->t_we = NULL;
	cub->t_ea = NULL;
	cub->t_s = NULL;
	cub->floor = NULL;
	cub->ceiling = NULL;
	cub->map = NULL;
	cub->gen.cols = 0;
	cub->gen.rows = 0;
	cub->gen.x_player = 0;
	cub->gen.y_player = 0;
	cub->gen.rot_angle = 0;
}

t_cub	cub_analyzecub(char *file)
{
	int		fd;
	char	*line;
	t_cub	cub;
	int		ret;

	init_cub(&cub);
	if ((fd = open(file, O_RDONLY)) == -1)
		print_exit(EBADFD, 2);
	while (get_next_line(fd, &line) > 0)
		ret = recognize_identifier(line, &cub);
	close(fd);
	cub.map[ret] = NULL;
	cub_validatemap(cub.map);
	cub.map = cub_formatmap(cub.map, &cub);
	cub_validatevars(cub);
	return (cub);
}
