# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasantos <tasantos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/10 23:15:25 by lmarques          #+#    #+#              #
#    Updated: 2022/08/16 18:06:31 by tasantos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = example

SRC = example.c \


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -C minilibx
		mv minilibx/libmlx.a .
		gcc -Wall -g -Werror -Wextra -c $(SRC)
		gcc -Wall -g -Werror -Wextra -L. -lmlx -lX11 -lXext $(OBJ) -o $(NAME)

clean:
		make -C minilibx clean
		rm -rf $(OBJ) libft.a libmlx.a

fclean: clean
		make -C minilibx clean
		rm -rf $(NAME)

re : fclean all
