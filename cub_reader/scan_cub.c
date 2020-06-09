/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:27:39 by caio              #+#    #+#             */
/*   Updated: 2020/06/09 16:13:28 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*void	get_map(char *s)
{

}*/

void	get_rgb(char *s, t_cub *cub)
{
	char *r;
	char *g;
	char *b;
	int i;
	int j;

	i = 0;
	j = 0;
	if (((r = (char*)ft_calloc(4, sizeof(char))) &&
		(g = (char*)ft_calloc(4, sizeof(char))) &&
		(b = (char*)ft_calloc(4, sizeof(char)))))
	{
		while (ft_isdigit(s[i]))
			r[j++] = s[i++];
		j = 0;
		i++;
		while (ft_isdigit(s[i]))
			g[j++] = s[i++];
		j = 0;
		i++;
		while (ft_isdigit(s[i]))
			b[j++] = s[i++];
	}
	r = ft_itoa_base(ft_atoi(r), 16);
	g = ft_itoa_base(ft_atoi(g), 16);
	b = ft_itoa_base(ft_atoi(b), 16);
	printf("%s %s %s\n", r, g, b);	
}

void	get_resolution(char *s, t_cub *cub)
{
	int i;
	int j;
	char *width;
	char *height;
	
	i = 0;
	i = ft_digitlen(s);
	width = ft_substr(s, 0, i);
	if (ft_isspace(s[i]))
		i++;
	j = i;
	i = ft_digitlen(&s[i]);
	height = ft_substr(s, j, i);
	cub->width = ft_atoi(width);
	cub->height = ft_atoi(height);
}

void	recognize_identifier(char *s, t_cub *cub)
{	
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
		get_rgb(&s[2], cub);
	else if (s[0] == 'C')
		get_rgb(&s[2], cub);
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
	cub->floor_color = 0;
	cub->ceiling_color = 0;
	cub->map = 0;
}

void	scan_cub()
{
	int	fd;
	char	*line;
	int	ret;
	t_cub	cub;
	
	init_cub(&cub);
	fd = open("cub3d.cub", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
		recognize_identifier(line, &cub);
	
	//printf("R %d %d\nNO %s\nSO %s\nWE %s\nEA %s\nS %s\n", cub.width, cub.height, cub.t_no, cub.t_so, cub.t_we, cub.t_ea, cub.t_s);
	close(fd);
}

int main(void)
{
	scan_cub();
}
