# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

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

typedef struct s_table
{
	t_token	*tkn_type;
	char	*name;
	char	*obj;
}t_table;

typedef struct	s_lex
{
	t_token	tkn_type;
	t_table	*tbl;
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

int get_token(char *input)
{
	char	*mnp_input;
	pid_t	pid;
	t_lex	*head;

	mnp_input = ft_strdup(input);
	pid = fork();
	if (pid == 0)
		child(mnp_input, &head);
	else
		parent();
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
