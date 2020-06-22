/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save_bitmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:02:51 by caio              #+#    #+#             */
/*   Updated: 2020/06/22 12:23:16 by caio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

t_file_header	init_file_header(t_file_header file_h)
{
	ft_memcpy(&file_h.bitmap_type, "BM", 2);
	file_h.file_size = (14 + 40) + 4 * 600 * 400;
	file_h.reserved1 = 0;
	file_h.reserved2 = 0;
	file_h.headers_bytes = FILE_HEADER_BYTES + BITMAP_HEADER_BYTES;
	return (file_h);
}

t_img_header	init_img_header(t_img_header img_h)
{
	img_h.size_header = BITMAP_HEADER_BYTES;
    img_h.width = 600;
    img_h.height = 400;
    img_h.planes = 1;
    img_h.bpp = BITS_PER_PIXEL;
    img_h.compression = 0;
    img_h.image_size = (14 + 40) + 4 * 600 * 400;
    img_h.x_ppm = 96 * 39.375;
    img_h.y_ppm = 96 * 39.375;
    img_h.total_colors = 0;
    img_h.important_colors = 0;
	return (img_h);
}

int	bmp_save_bitmap(char *image)
{
	int fd;
	int i;
	t_file_header	file_h;
	t_img_header	img_h;

	i = 0;
	file_h = init_file_header(file_h);
	img_h = init_img_header(img_h);
	fd = open("cub3d.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR |
			S_IRGRP | S_IROTH);
	write(fd, &file_h, 14);
	write(fd, &img_h, 40);

	while (i < 600 * 400)
	{
		write(fd, &image[i * 4], 3);
		i++;
	}
	close(fd);
	return (0);
}

/*int main(void)
{
	void *init;
	void *win;
	t_data data;
	int i;
	int j;

	i = 0;
	j = 0;
	init = mlx_init();
	data.img = mlx_new_image(init, 600, 400);
	data.img_addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length,
			&data.endian);
	win = mlx_new_window(init, 600, 400, "bmp_test");
	while (i < 600)
	{
		while (j < 200)
		{
			game_mlxpixelput(&data, i, j, 0xFFFFFF);
			j++;
		}
		while (j < 400)
		{
			game_mlxpixelput(&data, i, j, 0x000000);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(init, win, data.img, 0, 0);
	bmp_save_bitmap(data.img_addr);
	mlx_loop(init);
}*/
