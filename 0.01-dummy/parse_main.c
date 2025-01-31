#include "main_include.h"
#include "parse_main.h"
#include "table.h"

t_exec_env	*create_exec_env()
{
	t_exec_env	*exec_env;

	exec_env = malloc(sizeof(t_exec_env));
	exec_env->input_fd = STDIN_FILENO;
	exec_env->output_fd = STDOUT_FILENO;
	exec_env->error_fd = STDERR_FILENO;
	exec_env->exit_status = 0;
	return(exec_env);
}

void	*parse_function(char *input)
{
	t_node	*node;
	t_exec_env	*exec_env;

	exec_env = create_exec_env();
	node = quote_state(input);
	
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_node	*head;

	while (1)
	{
		input = readline("minishell> ");
		*(ft_strrchr(input, '\0')) = '\n';
		quote_state(input);
		if (input == NULL)
			break;
		if (ft_strlen(input) == 0)
			free(input);
		add_history(input);
		get_token(input);
	}
}
