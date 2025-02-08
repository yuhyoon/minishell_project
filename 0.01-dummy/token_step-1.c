#include "parse_main.h"

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

int	vaild_quote(char *s, int quote_flag)
{
	char *start;
 	int single_quote_open;
	int double_quote_open;
	int	i;

	single_quote_open = 0;
	double_quote_open = 0;
	i = 0;
	while (s[i] != '\0') 
	{
		if (s[0] == '\"')
		{
			if (s[i] == '\'')
				single_quote_open++;
			else if (s[i] == '\"')
			{
				double_quote_open++;
				if (double_quote_open == 2)
					break;
			}
		}
		else if (s[0] == '\'')
		{
			if (s[i] == '\"')
				double_quote_open++;
			else if (s[i] == '\'')
			{
				single_quote_open++;
				if (single_quote_open == 2)
					break;
			}
		}
		i++;
	}
	if ((single_quote_open % 2 != 0) || (double_quote_open % 2 != 0))
		return (0);
	return (1);
}

void	set_char_state(char *s, t_char_state *char_state)
{
	//char -> int 변경
	int	quote_flg;

	//*s -> s로 변경
	quote_flg = is_quote(s);
	if (quote_flg > 0)
		char_state->quote = valid_quote(s, quote_flg);
	char_state->current = s;
}

void	handle_putchar(t_char_state *char_state, int fd)
{
	char	*buf;
	int		size;

	if (char_state->quote == 0)
	{
		if (is_whitespace(char_state->current))
			ft_putchar_fd('\0', fd);
		else
			ft_putchar_fd(*(char_state->current), fd);
	}	
	else
	{
		size = read(fd + 1, buf, 1);
		while (size > 0)
		{
			if (char_state->quote < 0)
			{
				if (is_whitespace(char_state->current))
					ft_putchar_fd('\0', fd);
				else
					ft_putchar_fd(*buf, fd);
			}
			else
			{
				if (*buf == char_state->quote)
					ft_putchar_fd('\0', fd);
				else
					ft_putchar_fd(*buf, fd);
			}
			size += read(fd + 1, buf, 1);
		}
		close(fd + 1);
		unlink(fd + 1);
		char_state->quote = 0;
		char_state->current += size;
	}
}

int write_replace_spaces(char *s, int replace_fd)
{
	t_char_state	char_state;
	int				i;
	
	init_char_state(&char_state);
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
	char s[] = "    grep \"a1 e\"";
	int	replace_fd;
	char	*ready_str;

	replace_fd = open("split_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write_replace_spaces(s, replace_fd);
	ready_str = get_next_line(replace_fd);
	close(replace_fd);
	
}