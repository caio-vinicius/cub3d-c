/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:02:08 by caio              #+#    #+#             */
/*   Updated: 2020/06/23 11:41:01 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# define FILE_HEADER_BYTES 14
# define BITMAP_HEADER_BYTES 40
# define BITS_PER_PIXEL 24

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "cub3d.h"
# include "libft.h"

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
	unsigned int	width;
	unsigned int	height;
	short int	planes;
	short int	bpp;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	x_ppm;
	unsigned int	y_ppm;
	unsigned int	total_colors;
	unsigned int	important_colors;
} __attribute__((packed)) t_img_header;

typedef struct		s_bitmap_headers {
	t_file_header	file_h;
	t_img_header	img_h;
}			t_headers;

int	bmp_save_bitmap		(t_data data, t_cub cub);

#endif
