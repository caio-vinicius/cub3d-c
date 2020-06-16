/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_analyzecub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:27:39 by caio              #+#    #+#             */
/*   Updated: 2020/06/15 23:09:21 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	recognize_identifier(char *s, t_cub *cub)
{
	static int j;

	if (s[0] == 'R')
		cub_getr(&s[2], cub);
	else if (s[0] == 'N' && s[1] == 'O')
		cub->t_no = &s[3];
	else if (s[0] == 'S' && s[1] == 'O')
		cub->t_so = &s[3];
	else if (s[0] == 'W' && s[1] == 'E')
		cub->t_we = &s[3];
	else if (s[0] == 'E' && s[1] == 'A')
		cub->t_ea = &s[3];
	else if (s[0] == 'S')
		cub->t_s = &s[2];
	else if (s[0] == 'F')
		cub->floor = cub_getrgb(&s[2], cub);
	else if (s[0] == 'C')
		cub->ceiling = cub_getrgb(&s[2], cub);
	else if (cub_isstrmap(s))
		cub->map = cub_getmap(s, j++);
	else if (s[0] == '\0')
		return (0);
	else
		print_err_exit(EBADCUB);
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
	cub->cols = 0;
	cub->rows = 0;
}

void	cub_analyzecub(char *file)
{
	int		fd;
	char	*line;
	t_cub	cub;
	int		ret;

	init_cub(&cub);
	if ((fd = open(file, O_RDONLY)) == -1)
		print_err_exit(EBADFD);
	while (get_next_line(fd, &line) > 0)
		ret = recognize_identifier(line, &cub);
	close(fd);
	cub.map[ret] = NULL;
	cub_validatevars(cub);
	cub_validatemap(cub.map);
	cub.map = cub_formatmap(cub.map, &cub);

	//printf("R %d %d\nNO %s\nSO %s\nWE %s\nEA %s\nS %s\nF %s\nC %s\nM1 %s\nM2 %s\nM3 %s\nM4 %s\nCOLS %d\nROWS %d\n", cub.width, cub.height, cub.t_no, cub.t_so, cub.t_we, cub.t_ea, cub.t_s, cub.floor, cub.ceiling, cub.map[0], cub.map[1], cub.map[2], cub.map[3], cub.cols, cub.rows);
}
/*
int main(int argc, char *argv[])
{
	parsing_cub(argv[1]);
}*/
