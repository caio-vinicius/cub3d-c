# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caio <csouza-f@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/27 18:16:34 by caio              #+#    #+#              #
#    Updated: 2020/05/25 13:28:38 by nayran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d.a

SRCS = main.c

OBJS = main.o

all: $(NAME)

$(NAME): $(OBJS)
	clang -g $(OBJS) -lmlx
	ar rcs $@ $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
