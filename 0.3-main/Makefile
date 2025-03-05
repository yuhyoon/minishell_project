NAME = minish

CC = cc
CFLAGS = -g #-Wall -Wextra -Werror 
SRCS = main.c \
signals.c \
stack.c \
delete.c \
error.c \
analysis_redirect.c \
analysis_quote.c \
analysis_syntax.c \
analysis_dollar.c \
execution_cmd.c \
execution_redirect.c \
parse_step-1_utils.c \
parse_step-1_mask.c \
parse_step-2_handle_tokens.c \

#heredoc_1.c

READLINEFLG = -lreadline

LIBFTA = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

all: libft $(NAME)

libft:
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFTA)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) $(READLINEFLG) -o $(NAME)

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

.PHONY: all clean fclean re libft
