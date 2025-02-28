#ifndef PARSER_H
# define PARSER_H

# include "main.h"

typedef enum s_token
{
	NONE,
	TEXT,
	IN_RD,
	OUT_RD,
	DOLLAR,
	PIPE
}t_token;

typedef struct s_redrct
{
	char	*obj;
	int		parts;
	int		access;
	int		fd;
	char	type;
}t_redrct;

typedef struct s_char_state
{
	int	quote;
	int		quote_seq;
	char	*current;
}t_char_state;

typedef struct s_ready
{
	t_list	*text;
	t_list	*rdrct;
	int		rdrct_num;
	t_redrct	*rdrct_in;
	t_redrct	*rdrct_out;
	int		input;
	int		output;
}t_ready;

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
