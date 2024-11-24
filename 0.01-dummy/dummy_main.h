# include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

#define OPERAND 0
#define OPERATOR 1 

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}t_node;

typedef enum
{
	EQUAL,
	D_QUOTE,
	S_QUOTE,
	REDIRECT,
	PIPE,
	CMD,
} token_type;

typedef struct s_token{
	int			oper_type;
	token_type 	tkn_type;
    char		*input_src;
}t_token;