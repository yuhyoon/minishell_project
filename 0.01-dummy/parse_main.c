# include "table.h"



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

int	apply_fork(t_eval_1 *mnp)
{
	pid_t	pid;
	t_lex	*head;

	pid = fork();
	if (pid == 0)
		child(mnp, &head);
	else
		parent();
}

t_eval_1 *f(char *input)
{
	char	*mnp;
	t_eval_1	*eval_1;
	
	if (eval1_input(mnp, input))
	{
		//malloc t_eval_1
	}

}

int	main()
{
	char	*input;
	t_eval_1		*eval_1;
	t_node	*head;

	while (1)
	{
		input = readline("minishell> ");
		eval_1 = f(input);
		if (eval_1 == NULL)
			exit();
		apply_fork(eval_1);
		if (input == NULL)
			break;
		if (ft_strlen(input) == 0)
			free(input);
		add_history(input);
		get_token(input);
	}
}
