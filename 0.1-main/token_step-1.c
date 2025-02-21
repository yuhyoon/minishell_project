#include "parse_main.h"
#include "token_step-1_utils.h"
#include "token_step-1_stack.c"
# include "gnl_realreal_final.c"

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

void	store_quote_seq(t_char_state *char_state, int len, char *ss)
{
	int		quote_fd;
	int	i = 0;

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

	init_stack(&stack, NULL, ft_strlen(s));
	ss = s;
	push(&stack, *ss);
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
	store_quote_seq(state, i, ss);
	return (0);
}

void	set_char_state(char *s, t_char_state *char_state)
{
	char_state->quote = is_quote(*s);
	if (char_state->quote > 0)
		valid_quote(s, char_state->quote, char_state);
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


int	handle_putchar(t_char_state *char_state, int fd)
{
	int	size;

	size = 0;
	if (char_state->quote == 0)
	{
		size = putchar_quote_state_zero(char_state->current, fd);
	}	
	else
		size = read_store_fd(fd);
	return (size);
}

int write_replace_spaces(char *s, int replace_fd)
{
	t_char_state	char_state;
	int				i;
	int	len;
	
	init_char_state(&char_state, s);
	i = 0;
	while (*(char_state.current) != '\0')
	{
		set_char_state(char_state.current, &char_state);
		(char_state.current) += handle_putchar(&char_state, replace_fd);
	}
	if (*(char_state.current) == '\0')
	{	
		ft_putchar_fd('\n', replace_fd);
	}
	return (0);
}
int	valid_meta(int token, char *mask)
{
	int	max;
	int	i;
	int	rsult;

	i = 0;
	rsult = 0;
	if (token == IN_RD || token == OUT_RD)
		max = 3;
	else if (token == PIPE)
		max = 2;
	while (i < max && mask[i] == token)
		i++;
	if (i == max)
		rsult = 3;
	return (rsult);
}

int	syntax_analysis(char *mask)
{
	int	i;
	int	cnt;
	int	meta;
	int	err_flg;

	i = 0;
	cnt = 0;
	err_flg = 0;
	while (mask[i] != '\n' && err_flg == 0)
	{
		meta = ft_ismeta(&mask[i]);
		if (meta > 0)
			err_flg = valid_meta(mask[i], &mask[i]);
		i++;
	}
	return (err_flg);
}

char *generate_mask(char *s)
{
	int	mask_fd;
	char	*mask;
	int	len;
	struct stat	st;

	printf("s len: %ld\n", ft_strlen(s));
	mask_fd = open("mask_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write_replace_spaces(s, mask_fd);
	close(mask_fd);
	mask_fd = open("mask_fd", O_RDONLY);
	fstat(mask_fd, &st);
	len = (int)st.st_size;
	mask = malloc(sizeof(char) * len);
	read(mask_fd, mask, len);
	if (syntax_analysis(mask) > 0)
		exitcode = 3;
	close(mask_fd);
	unlink("mask_fd");
	return (mask);
}
