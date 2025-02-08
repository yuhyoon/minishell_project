typedef enum s_token
{
	NONE,
	IN_RD,
	OUT_RD,
	DOLLAR,
	PIPE
}t_token;

typedef struct s_char_state
{
	//int인데 깜빡한 듯?
	// char	quote;
	int		quote;
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

