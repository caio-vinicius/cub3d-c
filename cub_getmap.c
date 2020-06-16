/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_getmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:31:30 by caio              #+#    #+#             */
/*   Updated: 2020/06/15 23:01:46 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//thank you sfreitas.
char	**cub_getmap(char *s, int j)
{
	char			**tmp;
	static char		**map;
	int				i;
	//static int		j;

	i = 0;
	tmp = malloc((j + 1) * sizeof(char*));
	if (map)
	{
		while (i < j)
		{
			tmp[i] = map[i];
			i++;
		}
		free(map);
	}
	tmp[j] = s;
	map = tmp;
	//j++;
	return (map);
}