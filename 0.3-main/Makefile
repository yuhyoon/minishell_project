NAME = minish

CC = cc
CFLAGS = -g #-Wall -Wextra -Werror 
SRCS = main.c \
signals.c \
stack.c \
delete.c \
error.c \
free.c \
child_process.c \
analysis_redirect.c \
analysis_quote.c \
analysis_syntax.c \
analysis_dollar.c \
execution_cmd.c \
execution_builtins.c \
execution_redirect.c \
parse_step-1_utils.c \
parse_step-1_mask.c \
parse_step-2_handle_tokens.c \
builtin_init.c \
builtin_cd.c \
builtin_echo.c \
builtin_export.c \
builtin_pwd.c \
builtin_unset.c \
builtin_utils.c \
builtin_utils1.c \
bulitin_env.c\
builtin_exit.c \
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
	make bonus -C libft clean
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

VALGRIND_LOG = valgrind_log.txt

run: $(NAME)
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--suppressions=suppression_readline.supp \
		--show-reachable=yes \
		--track-fds=yes ./$(NAME) #2> $(VALGRIND_LOG)

re: fclean all

.PHONY: all clean fclean re libft
