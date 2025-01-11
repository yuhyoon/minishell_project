typedef enum s_token
{
	none,
	cmd,
	builtin,
	redirct,
	env_var,
	pipe
}t_token;

typedef struct s_eval_1
{
	char	*mnp;
	int		pipe;
	int		*pipe_pos;
}t_eval_1;

typedef struct s_node
{
	void	*content;
	struct s_node	*next;
}t_node;

typedef struct	s_lex
{
	t_token	tkn_type;
	void	*tbl;
}t_lex;