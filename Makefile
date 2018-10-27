# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/26 16:22:09 by dmendelo          #+#    #+#              #
#    Updated: 2018/10/27 16:36:35 by dmendelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = grimly

SRC = src/grimly.c \
	  src/bfs.c \
	  src/atoi_range.c \
	  src/checks.c \
	  src/matrix.c \
	  src/print_functions.c \
	  src/queue.c \
	  src/read.c \
	  src/trace.c \
	  src/free.c \

OBJ = grimly.o \
	  bfs.o \
	  atoi_range.o \
	  checks.o \
	  matrix.o \
	  print_functions.o \
	  queue.o \
	  read.o \
	  trace.o \
	  free.o

CFLAGS = -Wall -Wextra -Werror -I libft -I includes 

VPATH = src

all: $(NAME)

$(NAME): $(OBJ) 
		@make -C libft/
		@gcc $(OBJ) libft/libft.a -o $(NAME) 

clean:
		rm -rf $(OBJ)
		@make -C libft/ clean

fclean: clean
		rm -rf $(NAME)
		make -C libft/ fclean

re: fclean all
