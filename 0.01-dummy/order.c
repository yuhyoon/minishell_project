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

typedef struct s_str
{
    char    *start;
    char    *end;
}t_str;


void	push(char *meta, t_stack *stack, int *quote_flg)
{
	if (stack->top == -1)
    {
        stack->top = 0;
        stack->arr[stack->top] = *meta;
    }
	if (*quote_flg == 1 && *meta == '$')
		//push to stack

}

int f(char *s, int fd, t_stack *stack)
{
	t_stack	meta_stack;
	t_stack	quote_stack;
	int		quote_flg;

	while (*s != '\0')
	{
		if (ft_ismeta(*s) == false && is_whitespace(*s) == false)
			ft_putchar_fd(*s, fd);
		if (ft_ismeta(*s) == true)
		{
			push(*s, &meta_stack, &quote_flg);
		}
		else if (ft_isquote(*s) == true)
		{
			if (valid_quote(s, &quote_stack))
			{
				push(*s, &meta_stack, quote_flg);
			}	
			else
				ft_putchar_fd(*s, fd);
		}
		else if (is_whitespace(*s) == true)
		{
			ft_putchar_fd('\0', fd);
		}
		s++;
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