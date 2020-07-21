/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:22:38 by caio              #+#    #+#             */
/*   Updated: 2020/07/20 17:24:52 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRNO_H
# define ERRNO_H

# define CLOSECL 0 /* Sucess terminating process */
# define EBADFD 1 /* File descriptor in bad state */
# define ENSURRW 2 /* Map no surround by walls */
# define EBADCUB 3 /* Bad cub file */
# define EMISCUB 4 /* Missing cub file */
# define EMDIR 5 /* Missing position letter on map */
# define EPATH 6 /* Missing path of the map */ 
# define EFORMAT 7 /* File isn't .cub format */
# define EDOUBC 8 /* More than 1 same directive on cub file */

#endif
