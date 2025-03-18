#include "analysis.h"
#include "stack.h"

int	putchar_quote_state_zero(char *current, int fd)
{
	int	size;

	size = 0;
	if ((is_whitespace(*(current))))
		ft_putchar_fd(NONE, fd);
	else if (ft_ismeta((current)))
		ft_putchar_fd(ft_ismeta((current)), fd);
	else
		ft_putchar_fd(TEXT, fd);
	size++;
	return (size);
}

int read_store_fd(int fd)
{
	int		i;
	struct stat st;
	int		quote_fd;
	int		size;
	char	*buf;

	i = 0;
	quote_fd = fd + 1;
	fstat(quote_fd, &st);
	size = st.st_size;
	close(quote_fd);
	quote_fd = open("quote_fd", O_RDONLY, 0644);
	buf = malloc(sizeof(char) * size);
	read(quote_fd, buf, size);
	while (i < size)
	{
		ft_putchar_fd(buf[i], fd);
		i++;
	}
	close(quote_fd);
	free(buf);
	unlink("quote_fd");
	return (size);
}
void	store_quote_seq(t_char_state *char_state, int len)
{
	int		quote_fd;
	int		i;

	i = 0;
	quote_fd = open("quote_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (i < len)
	{
		if (char_state->quote < 0)
		{
			putchar_quote_state_zero(&(char_state->current[i]), quote_fd);
		}
		else if (char_state->quote > 0)
			{
				if (char_state->quote == '\"' && ft_ismeta(&(char_state->current[i])) == DOLLAR)
					ft_putchar_fd(DOLLAR, quote_fd);
				else if (char_state->current[i] == char_state->quote)
					ft_putchar_fd(NONE, quote_fd);
				else
					ft_putchar_fd(TEXT, quote_fd);
			}
		i++;
	}
}

int	valid_quote(char *s, int quote, t_char_state *state)
{
	t_stack stack;
	char	*ss;
	int		i = 1;

	init_stack(&stack, NULL, 0);
	ss = s;
	push(&stack, ss);
	while (is_emthy(&stack) == false && ss[i] != '\0')
	{
		if (is_quote(ss[i]) == quote)
		{	
			pop(&stack);
		}
		i++;		
	}
	if (is_emthy(&stack) == false && ss[i] == '\0')
		state->quote *= -1;
	store_quote_seq(state, i);
	return (0);
}
