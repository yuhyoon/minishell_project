#include "main_include.h"
#include "parse_main.h"
#include "table.h"

int	main()
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
