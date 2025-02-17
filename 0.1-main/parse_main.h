#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
#include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
#include <stdbool.h>
#include <string.h>
# include <fcntl.h>
#include <sys/stat.h>
# include "table.h"

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
	int	quote;
	int		quote_seq;
	char	*current;
}t_char_state;

// typedef struct	s_lex
// {
// 	t_token	tkn_type;
// 	void	*tbl;
// }t_lex;

// typedef struct s_node
// {
// 	struct s_lex	*content;
// 	struct s_node	*next;
// }t_node;

typedef struct s_ready
{
	t_list	*text;
	t_list	*io;
	t_list	*dolar;
	struct s_ready	*next;	
}t_ready;

typedef struct s_exe_info
{
	char	**cmd;
	int	in;
	int	out;
	struct s_exe_info	*next;
}t_exe_info;

typedef struct s_dollar
{
	char	pos;
	char	*str;
}t_dollar;

typedef struct s_stack
{
	int	size;
	struct s_list *top;
}t_stack;

typedef struct s_str
{
	char	*src;
	int	start;
	int	end;
}t_str;

#endif
