/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:27:39 by caio              #+#    #+#             */
/*   Updated: 2020/06/11 16:31:25 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	recognize_identifier(char *s, t_cub *cub)
{
	static int line;

	if (line == 0 && s[0] == 'R')
		get_resolution(&s[2], cub);
	else if (line == 1 && (s[0] == 'N' && s[1] == 'O'))
		cub->t_no = &s[3];
	else if (line == 2 && (s[0] == 'S' && s[1] == 'O'))
		cub->t_so = &s[3];
	else if (line == 3 && (s[0] == 'W' && s[1] == 'E'))
		cub->t_we = &s[3];
	else if (line == 4 && (s[0] == 'E' && s[1] == 'A'))
		cub->t_ea = &s[3];
	else if (line == 6 && (s[0] == 'S'))
		cub->t_s = &s[2];
	else if (line == 7 && s[0] == 'F')
		cub->floor = get_rgb(&s[2], cub);
	else if (line == 8 && s[0] == 'C')
		cub->ceiling = get_rgb(&s[2], cub);
	else if (line >= 10 && recognize_map(s))
		cub->map = get_map(s);
	else
		printf("Error\n");
	line++;
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
	cub->map = 0;
}

void	scan_cub()
{
	int		fd;
	char	*line;
	int		ret;
	t_cub	cub;

	init_cub(&cub);
	fd = open("cub3d.cub", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
		recognize_identifier(line, &cub);

	printf("R %d %d\nNO %s\nSO %s\nWE %s\nEA %s\nS %s\nC %s\nF %s\n", cub.width, cub.height, cub.t_no, cub.t_so, cub.t_we, cub.t_ea, cub.t_s, cub.floor, cub.ceiling);
	close(fd);
}

int main(void)
{
	scan_cub();
}
