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

typedef struct s_stack_pthes
{
    char    arr[1024];
    int     top;
}t_stack_pthes;

typedef struct s_str
{
    char    *start;
    char    *end;
}t_str;

void    f(t_stack_pthes *stack, char quote)
{
    if (stack->top == -1)
    {
        stack->top = 0;
        stack->arr[stack->top] = quote;
    }
    if (stack->arr[stack->top] == quote)
    {
        stack->arr[stack->top] = 0;
        stack->top--;
    }
    else
    {
        stack->top++;
        stack->arr[stack->top] = quote;
    }
}

void *valid_quotes(char *start, char quote)
{
    t_stack_pthes   stack;
    char            *end;
	t_str			*quoted;

	quoted = malloc(sizeof(t_str));
    quoted->end = start;

    //init stack
    stack.top = -1;

    //stack push
    f(&stack, *(quoted->end));
    while (stack.top != -1 && *(quoted->end) != '\0')
    {
        quoted->end++;
        if (*(quoted->end) == '\'' || *(quoted->end) == '\"')
            f(&stack, *(quoted->end));
    }
    if (stack.top == -1)
        quoted->start = start;
    else if (stack.top != -1)
        return (NULL);
	return (quoted);
}



void *ft_strtok_quote_new(char *str, char *delim, int *quote_sig)
{
    static t_str    s;
    int     len;
	char	*tmp;

    len = ft_strlen(delim);
    if (str != NULL)
	{
		tmp = ft_strchr(str, *delim);
        while (tmp == NULL || tmp != str)
        {	
			if (tmp != str)
			{
				str++;
				len = 0;
			}
			else
				len++;
			tmp = ft_strchr(str, &delim[len]);
		}
		if (tmp == str)
			s.start = str;
	}
    else if (*(s.end) == '\0')
        return (NULL);
	else
		s.start = s.end + 1;
    s.end = s.start;
	while (*(s.end) != '\0' && !(*(s.end) >= '\t' && *(s.end) <= '\r') && *(s.end) != ' ')
    {   
		if (*(s.end) != '\'')
			*quote_sig = '\'';
		else if (*(s.end) != '\"')
			*quote_sig = '\"';
		s.end++;
	}	
    if (*quote_sig == 0 && (*(s.end) == ' ' || (*(s.end) >= '\t' && *(s.end) <= '\r')))
		*(s.end) == '\0';
    return(s.start);   //confuse: malloc안하고 지역변수로 선언해도 살아있던가..
}

int main()
{
	char s[] = "    grep \"a1 e\"";
	char	*ptr;
	int	fd;
	t_str	*valid_quotes_flg;
	int		quote_sig[1];

	fd = open("valid_pthes", O_RDWR | O_CREAT | O_TRUNC, 0644);
	*quote_sig = 0;
	ptr = ft_strtok_quote_new(s, " \t\n\v\f\r", quote_sig);
    while (ptr != NULL && *quote_sig == 0)
    {
        ft_putendl_fd(ptr, fd);
		ptr = ft_strtok_quote_new(NULL, " \t\n\v\f\r" , quote_sig);
    }
	if (*quote_sig != 0)
		valid_quotes_flg = valid_quotes(ft_strchr(ptr, *quote_sig), *quote_sig);
	if (valid_quotes_flg == NULL)
		//ft_strtok(ptr, 공백) //공백을 찾아서 널로 바꿈
	else
	{
		//*quote_sig
		//ft_strtok(ptr, (char *)quote_sig) //quote를 찾아서 널로 바꿈
		// while (*ptr != *quote_sig)
		// {
		// 	ft_putchar_fd(*ptr, fd);
		// 	ptr++;
		// }
		// write(fd, "\0", 1);
		// *(ft_strrchr(ptr, " \t\n\v\f\r")) = '\0';

	}
}