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

typedef struct s_stack
{
    char    arr[1024];
    int     top;
}t_stack;

typedef struct s_char_state
{
	char	meta;
	int		quote;
	char	*current;
}t_char_state;

typedef struct s_str
{
    char    *start;
    char    *end;
}t_str;

void	set_char_state(char *s, t_char_state *char_state)
{
	char	quote_flg;

	quote_flg = is_quote(*s);
	if (quote_flg > 0)
		char_state->quote = valid_quote();
	char_state->meta = is_meta();
	char_state->current = s;
}

void	handle_putchar(t_char_state *char_state, int fd)
{
	char	*buf;
	int		size;

	if (char_state->quote <= 0)
	{
		if (is_whitespace(char_state->current))
			ft_putchar_fd('\0', fd);
		else
			ft_putchar_fd(*(char_state->current), fd);
	}	
	else if (char_state->quote > 0)
	{
		size = read(fd + 1, buf, 1);
		while (size > 0)
		{
			if (char_state->current == char_state->quote)
				ft_putchar_fd('\0', fd);
			ft_putchar_fd(*buf, fd);
			size = read(fd + 1, buf, 1);
		}
		close(fd + 1);
		char_state->quote = 0;
	}
}

int write_replace_spaces(char *s, int replace_fd)
{
	t_char_state	char_state;
	int				i;
	
	init_char_state(&char_state);
	i = 0;
	while (s[i] != '\0')
	{
		set_char_state(&s[i], &char_state);
		handle_putchar(&char_state, replace_fd);
		i++;
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