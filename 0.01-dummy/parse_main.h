typedef enum s_token
{
	none,
	cmd,
	builtin,
	redirct,
	env_var,
	PIPE
}t_token;

//필요없을수도..
// typedef struct exec_env
// {
// 	int	input_fd;
// 	int	output_fd;
// 	int	error_fd;
// 	int	exit_status;
// }t_exec_env;

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

