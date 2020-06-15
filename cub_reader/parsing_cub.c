/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:27:39 by caio              #+#    #+#             */
/*   Updated: 2020/06/15 16:08:24 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int is_wall(int c)
{
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}

int	ft_ptrlen(char **ptr)
{
	int y;

	y = 0;
	while (ptr[y])
		y++;
	return (y);
}

void	validate_map(char **map)
{
	int x;
	int y;
	int strlen;
	int ptrlen;

	x = 0;
	y = 0;
	ptrlen = ft_ptrlen(map);
	while (y < ptrlen - 1) //linha
	{
		strlen = ft_strlen(map[y]);
		while (x < strlen) //coluna
		{
			if (((y == 0 || y == ptrlen - 1) || (x == 0 || x == strlen - 1)) &&
					(!(is_wall(map[y][x]))))
				print_err_exit(ENSURRW);
			if ((y > 0 && y < ptrlen - 1) && (x > 0 && x < strlen - 1) &&
					(map[y][x] == '0') && ((!(is_c_map(map[y - 1][x]))) ||
					(!(is_c_map(map[y + 1][x]))) || (!(is_c_map(map[y][x - 1]))) ||
					(!(is_c_map(map[y][x + 1])))))
				print_err_exit(ENSURRW);
			x++;
		}
		x = 0;
		y++;
	}
}

int	recognize_identifier(char *s, t_cub *cub)
{
	static int j;

	if (s[0] == 'R')
		get_resolution(&s[2], cub);
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
		cub->floor = get_rgb(&s[2], cub);
	else if (s[0] == 'C')
		cub->ceiling = get_rgb(&s[2], cub);
	else if (is_l_map(s))
		cub->map = get_map(s, j++);
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
}

void	parsing_cub()
{
	int		fd;
	char	*line;
	t_cub	cub;
	int		j;

	init_cub(&cub);
	if ((fd = open("cub3d.cub", O_RDONLY)) == -1)
		print_err_exit(EBADFD);
	while (get_next_line(fd, &line) > 0)
		j = recognize_identifier(line, &cub);
	close(fd);
	cub.map[j] = NULL;
	validate_map(cub.map);
}

int main(void)
{
	parsing_cub();
}
