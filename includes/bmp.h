/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:02:08 by caio              #+#    #+#             */
/*   Updated: 2020/06/28 19:51:28 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# define FILE_HEADER_BYTES 14
# define BITMAP_HEADER_BYTES 12
# define BITS_PER_PIXEL 32

//remember to remove
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "cub3d.h"
# include "libft.h"

//ifndef check later
//check specific types later
//# include <stdint.h>

typedef struct		s_bitmap_file_header {
	unsigned char	bitmap_type[2];
	int		file_size;
	short		reserved1;
	short		reserved2;
	unsigned int	headers_bytes;
} __attribute__((packed)) t_file_header;

typedef	struct		s_bitmap_image_header {
	unsigned int	size_header;
	short int	width;
	short int	height;
	short int	planes;
	short int	bpp;
} __attribute__((packed)) t_img_header;

typedef struct		s_bitmap_headers {
	t_file_header	file_h;
	t_img_header	img_h;
}			t_headers;

#endif
