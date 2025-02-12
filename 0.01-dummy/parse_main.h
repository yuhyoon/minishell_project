#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
#include <stdio.h>
#include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
#include <stdbool.h>
#include "parse_main.h"
#include <string.h>
# include <fcntl.h>
#include <sys/stat.h>
# include "gnl_realreal_final.c"

typedef enum s_token
{
	NONE,
	TEXT,
	IN_RD,
	OUT_RD,
	DOLLAR,
	PIPE
}t_token;

typedef struct s_char_state
{
	//int인데 깜빡한 듯?
	// char	quote;
	int	quote;
	int		quote_seq;
	char	*current;
}t_char_state;

typedef struct	s_lex
{
	t_token	tkn_type;
	void	*tbl;
}t_lex;

typedef struct s_node
{
	struct s_lex	*content;
	struct s_node	*next;
}t_node;

typedef struct s_stack
{
	int	size;
	struct t_list *top;
}t_stack;

#endif
