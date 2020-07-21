# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/27 18:16:34 by caio              #+#    #+#              #
#    Updated: 2020/07/21 17:37:06 by caio             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = clang
CC_FLAGS = -Wall -Wextra -Werror

LIBRARY = libft/libft.a get_next_line/get_next_line.a minilibx-linux/libmlx.a

SRCS = $(SRCS_GAME) $(SRCS_CUB) $(SRCS_BMP) $(SRCS_INT)

SRCS_INT = game_sets.c game_sets2.c

SRCS_GAME = game.c game_mlxpixelput.c game_drawline.c game_distancepoints.c game_normalizeangle.c game_iswalkable.c game_castray.c game_rendermap.c game_renderrays.c game_renderwalls.c game_renderbackground.c game_moveplayer.c game_castallrays.c game_loop.c game_print_exit.c game_validateargs.c game_validatescreen.c game_rendersprites.c $(SRCS_INT)

SRCS_CUB = cub_analyzecub.c cub_formatmap.c cub_ptrlen.c cub_getmap.c cub_getr.c cub_getpath.c cub_getrgb.c cub_ischarmap.c cub_isstrmap.c cub_iswall.c cub_print_exit.c cub_validatemap.c cub_validatevars.c cub_getsprites.c

SRCS_BMP = bmp_save.c

OBJS = $(patsubst %.c, build/%.o, $(SRCS))

VPATH = srcs/game:srcs/cub:srcs/bmp

all: $(NAME)

$(NAME): $(OBJS) $(LIBRARY)
	$(CC) $^ -lm -lbsd -lXext -lX11 $(LIBRARY) -o $@

$(LIBRARY):
	$(MAKE) -C libft
	$(MAKE) -C get_next_line
	$(MAKE) -C minilibx-linux

build/%.o: %.c
	$(CC) -g $(CC_FLAGS) -c -o $@ $< -I includes/

clean:
	rm -rf $(OBJS)
	$(MAKE) clean -C libft
	$(MAKE) clean -C get_next_line
	$(MAKE) clean -C minilibx-linux

fclean: clean
	rm -rf $(NAME)

re: fclean all
