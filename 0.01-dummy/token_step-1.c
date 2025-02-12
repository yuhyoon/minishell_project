#include "parse_main.h"
#include "token_step-1_utils.c"
#include "token_step-1_stack.c"

typedef struct s_str
{
	char    *start;
	char    *end;
}t_str;


/*
void	valid_quote_hye(char *s, int quote_flag, t_char_state *state)
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
*/

void	store_quote_seq(t_char_state *char_state, int len, char *ss)
{
	int		quote_fd;
	int	i = 0;

	quote_fd = open("quote_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (i < len)
	{
		if (char_state->quote < 0)
			{
				if (is_whitespace(char_state->current[i]))
					ft_putchar_fd(NONE, quote_fd);
				else if (ft_ismeta(&(char_state->current[i])))
					ft_putchar_fd(ft_ismeta(&(char_state->current[i])), quote_fd);
				else
					ft_putchar_fd(TEXT, quote_fd);
			}
		else if (char_state->quote > 0)
			{
				if (char_state->quote == '\"' && ft_ismeta(&(char_state->current[i])) == DOLLAR)
					ft_putchar_fd(DOLLAR, quote_fd);
				else if (char_state->current[i] == char_state->quote)
				{	ft_putchar_fd(NONE, quote_fd); printf("quote :%d\n", NONE);}
				else
					ft_putchar_fd(TEXT, quote_fd);
			}
		i++;
	}
	//char_state->quote = 0;
}

int	valid_quote(char *s, int quote, t_char_state *state)
{
	t_stack stack;
	
	char	*ss;
	int		i = 1;

	init_stack(&stack, NULL, ft_strlen(s));
	ss = s;
	push(&stack, *ss);
	printf("stack\n");
	while (is_emthy(&stack) == false && ss[i] != '\0')
	{

		if (is_quote(ss[i]) == quote)
		{	
			printf("%d %d\n", i, ss[i]);
			pop(&stack);
		}
		i++;		
	}
	if (is_emthy(&stack) == false && ss[i] == '\0')
		state->quote *= -1;
	store_quote_seq(state, i, ss);
}

void	set_char_state(char *s, t_char_state *char_state)
{
	char_state->quote = is_quote(*s);
	if (char_state->quote > 0)
		valid_quote(s, char_state->quote, char_state);
}

int	handle_putchar(t_char_state *char_state, int fd)
{
	off_t	size;
	char	*buf;
	struct stat st;
	int		quote_fd;
	int		i = 0;

	size = 0;
	if (char_state->quote == 0)
	{
		if ((is_whitespace(*(char_state->current))))
			ft_putchar_fd(NONE, fd);
		else if (ft_ismeta((char_state->current)))
			ft_putchar_fd(ft_ismeta((char_state->current)), fd);
		else
			ft_putchar_fd(TEXT, fd);
		size++;
	}	
	else
	{
		quote_fd = fd + 1;
		fstat(quote_fd, &st);
		size = st.st_size;
		close(quote_fd);
		quote_fd = open("quote_fd", O_RDONLY, 0644);
		buf = malloc(sizeof(char) * size);
		read(quote_fd, buf, size);

		while (i < size)
		{
			printf("%d", buf[i]);
			ft_putchar_fd(buf[i], fd);
			i++;
		}
		printf("\n");
		close(quote_fd);
		free(buf);
	}
	return (size);
}

int write_replace_spaces(char *s, int replace_fd)
{
	t_char_state	char_state;
	int				i;
	int	len;
	
	init_char_state(&char_state, s);
	i = 0;
	printf("charstate.current\n");
	while (*(char_state.current) != '\0')
	{
		printf("%s start\n", char_state.current);
		set_char_state(char_state.current, &char_state);
		(char_state.current) += handle_putchar(&char_state, replace_fd);
		printf("%s\n", char_state.current);
	}
	if (*(char_state.current) == '\0')
	{		ft_putchar_fd('\n', replace_fd); printf("newline put\n");}
	return (0);
}

int main()
{
	char s[] = " \"a1\" HOME< 'a'sdf 'abd'";
	int	replace_fd;
	char	*mask;
	int	len;

	printf("s len: %d\n", ft_strlen(s));
	replace_fd = open("split_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write_replace_spaces(s, replace_fd);
	close(replace_fd);
	replace_fd = open("split_fd", O_RDONLY);
	mask = get_next_line(replace_fd);
	len = ft_strlen_delim(mask, '\n');
	printf("\nmask len: %d\n", len);
	for (int i = 0; i < ft_strlen(s); i++) {
        	printf("%c ", s[i]);
    }
	printf("\n");
}
