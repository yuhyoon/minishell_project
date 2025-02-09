#include "parse_main.h"
#include "token_step-1_utils.c"

typedef struct s_stack
{
	char    arr[1024];
	int     top;
}t_stack;

typedef struct s_str
{
	char    *start;
	char    *end;
}t_str;


void	valid_quote(char *s, int quote_flag, t_char_state *state)
{
	char *start;
 	int single_quote_open;
	int double_quote_open;
	int	i;

	single_quote_open = 0;
	double_quote_open = 0;
	i = 0;
	while (s[i] != '\0' && double_quote_open != 2 && single_quote_open != 2) 
	{
		if (s[0] == '\"')
		{
			if (s[i] == '\'')
				single_quote_open++;
			else if (s[i] == '\"')
				double_quote_open++;
		}
		else if (s[0] == '\'')
		{
			if (s[i] == '\"')
				double_quote_open++;
			else if (s[i] == '\'')
				single_quote_open++;
		}
		i++;
	}
	state->quote_seq = i;
	if ((single_quote_open % 2 != 0) || (double_quote_open % 2 != 0))
		state->quote *= -1;
}



void	set_char_state(char *s, t_char_state *char_state)
{
	//char -> int 변경
	int	quote_flg;

	//*s -> s로 변경
	char_state->quote = is_quote(*s);
	if (quote_flg > 0)
		valid_quote(s, char_state->quote, char_state);
}

void	handle_putchar(t_char_state *char_state, int fd)
{
	int		i;

	if (char_state->quote == 0)
	{
		if ((is_whitespace(*(char_state->current))))
			ft_putchar_fd('\0', fd);
		else
			ft_putchar_fd(*(char_state->current), fd);
	}	
	else
	{
		i = 0;
		printf("char_state->quote_seq: %d\n", char_state->quote_seq);
		while (char_state->quote_seq >= 0)
		{
			if (char_state->quote < 0)
			{
				if (is_whitespace(*(char_state->current)))
					ft_putchar_fd('\0', fd);
				else
					ft_putchar_fd(*(char_state->current), fd);
			}
			else
			{
				if (*(char_state->current) == char_state->quote)
					ft_putchar_fd('\0', fd);
				else
					ft_putchar_fd(*(char_state->current), fd);
			}
			char_state->current++;
			char_state->quote_seq--;
		}
		char_state->quote = 0;
		//char_state->current += char_state->quote_seq;
		char_state->current = 0;
	}
}

int write_replace_spaces(char *s, int replace_fd)
{
	t_char_state	char_state;
	int				i;
	
	init_char_state(&char_state, s);
	i = 0;
	while (*(char_state.current) != '\0')
	{
		set_char_state(char_state.current, &char_state);
		handle_putchar(&char_state, replace_fd);
		(char_state.current)++;
	}
	if (*s == '\0')
		ft_putchar_fd('\n', replace_fd);
	return (0);
}

int main()
{
	char s[] = " \"a1 e\"";
	int	replace_fd;
	char	*ready_str;

	replace_fd = open("split_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write_replace_spaces(s, replace_fd);
	ready_str = get_next_line(replace_fd);
	close(replace_fd);
}