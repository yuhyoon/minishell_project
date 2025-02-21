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
	char	type;
	int		parts;
	char	*obj;
	int		access;
	int		hrd_fd;
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
	t_redrct	*in;
	t_redrct	*out;
}t_ready;

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
