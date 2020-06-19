/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_analyzecub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:27:39 by caio              #+#    #+#             */
/*   Updated: 2020/06/19 14:41:52 by caio             ###   ########.fr       */
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
		cub_print_exit(EBADCUB);
	return (j);
}

t_cub	*init_cub()
{
	t_cub *cub;

	if (!(cub = malloc(sizeof(t_cub))))
		return (NULL);
	cub->width = 0;
	cub->height = 0;
	cub->t_no = NULL;
	cub->t_so = NULL;
	cub->t_we = NULL;
	cub->t_ea = NULL;
	cub->t_s = NULL;
	cub->map = NULL;
	cub->gen.cols = 0;
	cub->gen.rows = 0;
	cub->gen.x_player = 0;
	cub->gen.y_player = 0;
	cub->gen.rot_angle = 0;
	return (cub);
}

t_cub	*cub_analyzecub(char *file)
{
	int		fd;
	char	*line;
	t_cub	*cub;
	int		ret;

	cub = init_cub();
	if ((fd = open(file, O_RDONLY)) == -1)
		cub_print_exit(EBADFD);
	while (get_next_line(fd, &line) > 0)
		ret = recognize_identifier(line, cub);
	close(fd);
	cub->map[ret] = NULL;
	cub_validatemap(cub->map);
	cub->map = cub_formatmap(cub->map, cub);
	cub_validatevars(*cub);
	return (cub);
}

/*int	main(void)
{
	t_cub *cub;
	int i;

	i = 0;
	//segv when wrong file
	cub = cub_analyzecub("cub3d.cub");

	printf("R |%d| |%d|\nNO |%s|\nSO |%s|\nWE |%s|\nEA |%s|\nS |%s|\nF |%x|\nC |%x|\nM1 |%s|\nM2 |%s|\nM3 |%s|\nM4 |%s|\nCOLS |%d|\nROWS |%d|\n", cub->width, cub->height, cub->t_no, cub->t_so, cub->t_we, cub->t_ea, cub->t_s, cub->floor, cub->ceiling, cub->map[0], cub->map[1], cub->map[2], cub->map[3], cub->gen.cols, cub->gen.rows);

	free(cub->t_no);
	free(cub->t_so);
	free(cub->t_we);
	free(cub->t_ea);
	free(cub->t_s);
	while (cub->gen.rows > i)
	{
		free(cub->map[i]);
		i++;
	}
	free(cub);
}*/
