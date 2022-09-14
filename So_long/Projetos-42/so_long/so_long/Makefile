# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasantos <tasantos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 03:01:14 by tasantos          #+#    #+#              #
#    Updated: 2022/08/25 00:01:35 by tasantos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= so_long.a
INCLUDES_PATH	= ./includes
SOURCES_PATH	= ./src
OBJECTS_PATH	= ./objects
HEADERFILES		= libft.h ft_printf.h get_next_line.h 
GREEN			= \033[0;32m
RESET_COLOR		= \033[0m
SOURCEFILES		= ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strdup.c \
			ft_strmapi.c \
			ft_split.c \
			ft_itoa.c \
			ft_striteri.c \
			ft_printf_hex_len.c \
			ft_printf_ithex.c \
			ft_printf_pointer.c \
			ft_printf_putchar.c \
			ft_printf_putstr.c \
			ft_printf_uitoa.c \
			ft_printf.c \
			get_next_line.c \
			get_next_line_utils.c \
			
EXEC 			= gcc main.c -lX11 -lXext -lmlx
INCLUDES		= $(addprefix $(INCLUDES_PATH)/, $(HEADERFILES))
SOURCES			= $(addprefix $(SOURCES_PATH)/, $(SOURCEFILES))
OBJECTS			= $(addprefix $(OBJECTS_PATH)/, $(subst .c,.o,$(SOURCEFILES)))

STANDARD_FLAGS 		= -Wall -Werror -Wextra
MINILIBX_FLAGS		= -lmlx -lXext -lX11

VALGRIND		= @valgrind --leak-check=full --show-leak-kinds=all \
--track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes

all : $(NAME)

$(NAME): $(OBJECTS) $(INCLUDES)
	ar -rcs $(NAME) $(OBJECTS)
	@echo "$(NAME): $(GREEN) was compiled.$(RESET_COLOR)"
	@echo

$(OBJECTS_PATH)/%.o:	$(SOURCES_PATH)/%.c $(INCLUDES)
	mkdir -p $(OBJECTS_PATH)
	$(CC) -c $(STANDARD_FLAGS) -I $(INCLUDES_PATH) -c $< -o $@ 


exec:
	$(EXEC)
	
clean:
	rm -f $(NAME) $(OBJECTS)
	rm -rf	$(OBJECTS_PATH)

fclean: clean
		rm -f $(NAME)
		
re : fclean all

.PHONY: all clean fclean re
