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
	char	quote;
	char	*current;
}t_char_state;

typedef struct s_str
{
    char    *start;
    char    *end;
}t_str;


void	push(char *meta, t_stack *stack)
{
	if (stack->top == -1)
    {
        stack->top = 0;
        stack->arr[stack->top] = *meta;
    }
	if (*quote_flg == 1 && *meta == '$')
		//push to stack

}

void	set_char_state(char *s, t_char_state *char_state)
{
	char	quote_flg;

	quote_flg = is_quote(*s);
	if (quote_flg > 0)
		char_state->quote = valid_quote();
	char_state->meta = is_meta();
	char_state->current = s;
}

void	handle_putchar(t_char_state *char_state)
{
	if (char_state->quote <= 0)
	{
		if (is_meta(char_state->current))
			return ;
		else if (is_whitespace(char_state->current))
			ft_putchar_fd('\0', fd);
		else
			ft_putchar_fd(*(char_state->current), fd);
	}	
	else if (char_state->quote > 0)
	{
		if (char_state->dollar > 0)
		{
			return ;
		}
		if (char_state->current == char_state->quote)
			ft_putchar_fd('\0', fd);
		else
			ft_putchar_fd(*(char_state->current), fd);
		
	}
		
}

int f(char *s, int fd, t_stack *stack)
{
	t_stack	meta_stack;
	t_stack	quote_stack;
	char		quote_sig;
	t_char_state	char_state;

	quote_sig = 0;
	init_stack(&meta_stack, &quote_sig);
	while (s[i] != '\0')
	{
		set_char_state(&s[i], &char_state);
		handle_putchar(&char_state, &meta_stack, &quote_stack);
		handle_stack()
		i++;
    }
	if (*s == '\0')
		*s = '\n';
        
}

int main()
{
	char s[] = "    grep \"a1 e\"";
	char	*ptr;
	int	fd;
	t_str	*valid_quotes_flg;
	char    *quote_sig;

	fd = open("valid_pthes", O_RDWR | O_CREAT | O_TRUNC, 0644);
	quote_sig = NULL;
	ptr = s;

    while (ptr != NULL && quote_sig == NULL)
    {
		quote_sig = ft_strchr(ptr, '\'');
		if (quote_sig == NULL)
		    quote_sig = ft_strchr(ptr, '\"');
		if (quote_sig == NULL)
		{
        	ft_putendl_fd(ptr, fd);
			ptr = ft_strtok_quote_new(NULL, " \t");
		}
    }
	if (quote_sig != NULL)
		valid_quotes_flg = valid_quotes(quote_sig, *quote_sig);
	if (valid_quotes_flg == NULL)
		ft_strtok_quote_new(NULL, " \t"); //공백을 찾아서 널로 바꿈
	else
	{
		ft_strtok_quote_new(ptr, "\'\"");
	}
}