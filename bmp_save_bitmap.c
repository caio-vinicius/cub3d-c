/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save_bitmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:02:51 by caio              #+#    #+#             */
/*   Updated: 2020/07/07 14:43:01 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

static t_file_header	init_file_header(t_file_header file_h, t_cub cub)
{
	ft_memcpy(&file_h.bitmap_type, "BM", 2);
	file_h.file_size = (FILE_HEADER_BYTES + BITMAP_HEADER_BYTES) + 4 *
		cub.width * cub.height;
	file_h.reserved1 = 0;
	file_h.reserved2 = 0;
	file_h.headers_bytes = FILE_HEADER_BYTES + BITMAP_HEADER_BYTES;
	return (file_h);
}

static t_img_header	init_img_header(t_img_header img_h, t_cub cub)
{
	img_h.size_header = BITMAP_HEADER_BYTES;
    img_h.width = cub.width;
    img_h.height = cub.height;
    img_h.planes = 1;
    img_h.bpp = BITS_PER_PIXEL;
	return (img_h);
}

void	bmp_save_bitmap(t_data data, t_cub cub)
{
	t_headers	headers;
	int			fd;
	int			y;

	y = cub.height;
	headers.file_h = init_file_header(headers.file_h, cub);
	headers.img_h = init_img_header(headers.img_h, cub);
	fd = open("cub3d.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR |
			S_IRGRP | S_IROTH);
	write(fd, &headers.file_h, 14);
	write(fd, &headers.img_h, 12);

	while (--y >= 0)
		write(fd, &data.img_addr[y * data.line_length], data.line_length);
	close(fd);
}
