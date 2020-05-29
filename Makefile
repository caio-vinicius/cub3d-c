# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/27 18:16:34 by caio              #+#    #+#              #
#    Updated: 2020/05/27 15:47:19 by caio             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d.a

SRCS = main.c my_mlx_pixel_put.c dda_draw_line.c

OBJS = main.o my_mlx_pixel_put.o dda_draw_line.o

all: $(NAME)

$(NAME): $(OBJS)
	clang -g -Wall -Wextra -Werror $(OBJS) -lm -lbsd -lmlx -lXext -lX11
	ar rcs $@ $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
