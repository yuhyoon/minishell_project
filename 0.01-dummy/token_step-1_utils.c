# include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
#include <stdbool.h>
#include "parse_main.h"
#include <string.h>
# include <fcntl.h>

void	init_char_state(t_char_state *state)
{
	state->current = NULL;
	state->quote = 0;
}

int is_whitespace(char c)
{
    if ((c >= '\t' && c <= '\r') || c == ' ' )
        return (1);
    return (0);
}

//If true, return quote ascii
int	is_quote(char c)
{
	if (c == '\'')
		return ('\'');
	else if (c == '\"')
		return ('\"');
	return (0);
}

int ft_ismeta(char *input)
{
    if (*input == '<')
		return (IN_RD);
	else if (*input == '>')
		return (OUT_RD);
	else if (*input == '$')
		return (DOLLAR);
	else if (*input == '|')
		return (PIPE);
	else
		return (0);
}