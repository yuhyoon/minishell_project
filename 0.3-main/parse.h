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

//parse step 1
char 	*generate_mask(t_minish *sh);
int 	write_replace_spaces(char *s, int replace_fd);
int		handle_putchar(t_char_state *char_state, int fd);
void	set_char_state(char *s, t_char_state *char_state);

//parse step 2
void 	*parsing(t_minish *sh, int len);
int		handle_pipe(t_minish *sh, t_ready *current_rdy, t_list **rdrct, int save);
t_list *init_parsing_structure(t_list **rdy_head);
void	*create_rdy();
#endif
