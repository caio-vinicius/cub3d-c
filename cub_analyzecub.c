/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_analyzecub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:27:39 by caio              #+#    #+#             */
/*   Updated: 2020/07/07 12:57:24 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	recognize_identifier(char *s, t_cub *cub)
{
	if (s[0] == 'R')
		cub_getr(s, cub);
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
		cub->floor = cub_getrgb(s);
	else if (s[0] == 'C')
		cub->ceiling = cub_getrgb(s);
	else if (cub_isstrmap(s))
		cub->map = cub_getmap(s);
	/*else if (s[0] == '\0')
		free(s);
	else
		cub_print_exit(EBADCUB);*/
	free(s);
}

static t_cub	*init_cub()
{
	t_cub *cub;

	if (!(cub = malloc(sizeof(t_cub))))
		return (NULL);
	ft_bzero(cub, sizeof(t_cub));
	return (cub);
}

t_cub	*cub_analyzecub(char *file)
{
	int		fd;
	char	*line;
	t_cub	*cub;

	cub = init_cub();
	if ((fd = open(file, O_RDONLY)) == -1)
		cub_print_exit(EBADFD);
	while (get_next_line(fd, &line) > 0)
		recognize_identifier(line, cub);
	free(line);
	close(fd);
	cub_validatevars(*cub);
	cub_validatemap(cub->map);
	cub->map = cub_formatmap(cub->map, &cub->gen);
	cub_getsprites(cub->map, &cub->gen);
	if (!cub->gen.rot_angle)
		cub_print_exit(EMDIR);
	return (cub);
}
