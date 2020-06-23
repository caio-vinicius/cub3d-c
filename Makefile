# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/27 18:16:34 by caio              #+#    #+#              #
#    Updated: 2020/06/23 12:00:57 by caio             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBRARY = libft/libft.a get_next_line/get_next_line.a

SRCS = main.c game_mlxpixelput.c game_drawline.c game_distancepoints.c game_normalizeangle.c game_iswalkable.c game_castray.c game_drawsquare.c game_rendermap.c game_renderrays.c game_renderwalls.c game_renderbackground.c game_moveplayer.c game_castallrays.c game_loop.c game_print_exit.c $(SRCS_CUB) $(SRCS_BMP)

SRCS_CUB = cub_analyzecub.c cub_formatmap.c cub_ptrlen.c cub_getmap.c cub_getr.c cub_getpath.c cub_getrgb.c cub_ischarmap.c cub_isstrmap.c cub_iswall.c cub_print_exit.c cub_validatemap.c cub_validatevars.c

SRCS_BMP = bmp_save_bitmap.c

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
