# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/27 18:16:34 by caio              #+#    #+#              #
#    Updated: 2020/06/18 12:26:57 by caio             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBRARY = libft/libft.a get_next_line/get_next_line.a

SRCS = main.c my_mlx_pixel_put.c dda_draw_line.c distance_points.c normalize_angle.c is_walkable.c cast_ray.c draw_square_on_image.c render_map.c render_player.c render_rays.c render_walls.c render_background.c move_player.c cast_all_rays.c game_loop.c sum_rgb.c $(SRCS_CUB)

SRCS_CUB = cub_analyzecub.c cub_formatmap.c cub_ptrlen.c cub_getmap.c cub_getr.c cub_getpath.c cub_getrgb.c cub_ischarmap.c cub_isstrmap.c cub_iswall.c print_exit.c cub_validatemap.c cub_validatevars.c

OBJS = $(patsubst %.c, build/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBRARY)
	clang $^ -lm -lbsd -lmlx -lXext -lX11 $(LIBRARY) -o $@

$(LIBRARY):
	$(MAKE) -C libft
	$(MAKE) -C get_next_line

build/%.o: %.c
	clang -g -Wall -Wextra -Werror -c -o $@ $< -I includes/

clean:
	rm -rf $(OBJS)
	$(MAKE) clean -C libft
	$(MAKE) clean -C get_next_line

fclean: clean
	rm -rf $(NAME)

re: fclean all
