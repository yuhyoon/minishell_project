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

typedef struct s_char_state
{
	char		quote;
	char	*current;
}t_char_state;

void	init_char_state(t_char_state *state)
{
	state->current = NULL;
	state->quote = 0;
}

int is_whitespace(char c)
{
    if (c >= '\t' && c <= '\r' && c == ' ' )
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