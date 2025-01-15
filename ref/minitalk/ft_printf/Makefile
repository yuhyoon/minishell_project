# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 15:36:49 by hyeyeom           #+#    #+#              #
#    Updated: 2024/08/12 20:51:14 by hyeyeom          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRCS = main.c \
	libft/ft_itoa.c \
	libft/ft_itoh.c \
	libft/ft_itou.c \
	libft/ft_itop.c \
	parseft/ft_parse_char.c \
	parseft/ft_parse_dex.c \
	parseft/ft_parse_hex.c \
	parseft/ft_parse_pointer.c 

OBJS = $(SRCS:.c=.o)

all : $(NAME) 

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

%.o : %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

re : fclean all

.PHONY : all clean fclean re