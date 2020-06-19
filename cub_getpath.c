/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_getpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 12:24:34 by caio              #+#    #+#             */
/*   Updated: 2020/06/19 10:26:00 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*cub_getpath(char *s, int pos)
{
	char	*str;
	int		strlen;

	strlen = ft_strlen(&s[pos]);
	str = malloc(strlen * sizeof(char) + 1);
	if (str)
		str = ft_memcpy(str, &s[pos], strlen);
	str[strlen] = '\0';
	free(s);
	return (str);
}
