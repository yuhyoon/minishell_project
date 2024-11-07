# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 10:43:44 by yuhyoon           #+#    #+#              #
#    Updated: 2024/07/15 15:49:23 by yuhyoon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SRCS = error_exit.c \
close_free.c \
free_splited.c \
free_cmd_fp.c \
pipex_split.c \
create_pipe.c \
pipex.c

LIBFTA = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

all: libft $(NAME)

libft:
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFTA)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) -o $(NAME)

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

.PHONY: all clean fclean re libft
