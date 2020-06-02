# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/27 18:16:34 by caio              #+#    #+#              #
#    Updated: 2020/06/02 12:44:28 by caio             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d.a

SRCS = main.c my_mlx_pixel_put.c dda_draw_line.c distance_points.c normalize_angle.c is_walkable.c cast_ray.c draw_square_on_image.c render_map.c render_player.c render_rays.c render_walls.c render_background.c move_player.c cast_all_rays.c game_loop.c

OBJS = main.o my_mlx_pixel_put.o dda_draw_line.o distance_points.o normalize_angle.o is_walkable.o cast_ray.o draw_square_on_image.o render_map.o render_player.o render_rays.o render_walls.o render_background.o move_player.o cast_all_rays.o game_loop.o

all: $(NAME)

$(NAME): $(OBJS)
	@clang -g -Wall -Wextra -Werror $(OBJS) -lm -lbsd -lmlx -lXext -lX11
	@ar rcs $@ $<

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
