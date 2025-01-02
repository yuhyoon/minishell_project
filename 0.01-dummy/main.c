# include "table.h"

typedef enum s_token
{
	cmd,
	builtin,
	redirct,
	env_var,
	pipe
}t_token;

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

int	child(char *mnp, t_lex *head)
{
	lex_analysis(mnp);
}

int	parent()
{
	if (syntax_analysis())
		apply();
	else
		error();
}

int	circulate(void *mnp)
{
	if (is_pipe(mnp) == false)
		mnp = (char *)mnp;
	else
		mnp = (t_pipe *)mnp;
///todo: add - error handling///	
	pid_t	pid;
	t_lex	*head;

	pid = fork();
	if (pid == 0)
		child(mnp, &head);
	else
		parent();
}

int	is_pipe(void *mnp)
{
	if (((t_pipe *)mnp)->is_pipe == 0)
		return (false);
	else
		return (true);
}

int maniplte_input(char *input)
{
	void	*mnp;

	mnp = manipulate(input);
}

int	main()
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break;
		if (ft_strlen(input) == 0)
			free(input);
		add_history(input);
		get_token(input);
	}
}
