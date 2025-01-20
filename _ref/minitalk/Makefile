# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 15:36:49 by hyeyeom           #+#    #+#              #
#    Updated: 2024/08/12 21:34:35 by hyeyeom          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME   = client
NAMES = server
NAMEBC = client_bonus
NAMEBS = server_bonus
ATOI = ft_atoi.o
LIBFT = libftprintf.a
CP_LIBFT = ft_printf/libftprintf.a

SRCS = client.c \
	server.c \
	ft_atoi.c \
	client_bonus.c \
	server_bonus.c

all : $(LIBFT)
	
$(LIBFT) : $(CP_LIBFT)
	cp ft_printf/libftprintf.a ./$(LIBFT)

$(CP_LIBFT) :
	make -C ft_printf

manda : $(NAME) $(NAMES)

bonus : $(NAMEBC) $(NAMEBS)

$(NAME) : client.o ft_atoi.o
	$(CC) $(CFLAGS) client.o ft_atoi.o libftprintf.a -o $(NAME)

$(NAMES) : server.o
	$(CC) $(CFLAGS) server.o libftprintf.a -o $(NAMES)

$(NAMEBC) : client_bonus.o ft_atoi.o
	$(CC) $(CFLAGS) client_bonus.o ft_atoi.o libftprintf.a -o $(NAMEBC)

$(NAMEBS) : server_bonus.o
	$(CC) $(CFLAGS) server_bonus.o libftprintf.a -o $(NAMEBS)

$(ATOI) : ft_atoi.c
	$(CC) $(CFLAGS) -c ft_atoi.c

server_bonus.o : server_bonus.c minitalk_bonus.h
	$(CC) $(CFLAGS) -c server_bonus.c

client_bonus.o : client_bonus.c minitalk_bonus.h
	$(CC) $(CFLAGS) -c client_bonus.c

server.o : server.c minitalk.h
	$(CC) $(CFLAGS) -c server.c

client.o : client.c minitalk.h
	$(CC) $(CFLAGS) -c client.c

OBJS = $(SRCS:.c=.o)

clean :
	rm -f $(OBJS) $(OBJS:.o=_bonus.o)
	make clean -C ft_printf

fclean : clean
	rm -f $(NAME) $(NAMES) libftprintf.a
	make fclean -C ft_printf

fclean_bonus : clean 
	rm -f $(NAMEBC) $(NAMEBS) libftprintf.a
	make fclean -C ft_printf

re : fclean all manda

re_bonus : fclean_bonus all bonus

.PHONY : all clean fclean fclean_bonus re re_bonus manda bonus