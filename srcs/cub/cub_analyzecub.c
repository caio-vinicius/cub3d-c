/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_analyzecub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:27:39 by caio              #+#    #+#             */
/*   Updated: 2020/07/20 21:55:04 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int		recognize_identifier(char *s, t_cub *cub, int i)
{
	if ((s[0] == '\n' || s[0] == ' ' || s[0] == '\0'))
		(void)s;
	else if (s[0] == 'R' && ++i)
		cub_getr(s, cub);
	else if (s[0] == 'N' && s[1] == 'O' && ++i)
		cub->t_no = cub_getpath(s, 3);
	else if (s[0] == 'S' && s[1] == 'O' && ++i)
		cub->t_so = cub_getpath(s, 3);
	else if (s[0] == 'W' && s[1] == 'E' && ++i)
		cub->t_we = cub_getpath(s, 3);
	else if (s[0] == 'E' && s[1] == 'A' && ++i)
		cub->t_ea = cub_getpath(s, 3);
	else if (s[0] == 'S' && ++i)
		cub->t_s = cub_getpath(s, 2);
	else if (s[0] == 'F' && ++i)
		cub->floor = cub_getrgb(s);
	else if (s[0] == 'C' && ++i)
		cub->ceiling = cub_getrgb(s);
	else if (cub_isstrmap(s))
		cub->map = cub_getmap(s);
	else
		cub_print_exit(EBADCUB);
	free(s);
	(i > 8) ? cub_print_exit(EDOUBC) : 0;
	return (i);
}

static t_cub	*init_cub(void)
{
	t_cub *cub;

	if (!(cub = malloc(sizeof(t_cub))))
		return (NULL);
	ft_bzero(cub, sizeof(t_cub));
	return (cub);
}

t_cub			*cub_analyzecub(char *file)
{
	int			fd;
	char		*line;
	static int	i;
	t_cub		*cub;

	if (ft_strncmp(ft_strrchr(file, '.'), ".cub", 3))
		cub_print_exit(EFORMAT);
	cub = init_cub();
	if ((fd = open(file, O_RDONLY)) == -1)
		cub_print_exit(EBADFD);
	while (get_next_line(fd, &line) > 0)
		i = recognize_identifier(line, cub, i);
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
