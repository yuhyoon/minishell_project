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

    end = start;
    //init stack
    stack.top = -1;

    //stack push
    f(&stack, *end);
    while (stack.top != -1 && *end != '\0')
    {
        end++;
        if (*end == '\'' || *end == '\"')
            f(&stack, *end);
    }
    if (stack.top == -1)
        return (end);
    else if (stack.top != -1 && *end =='\0')
        return (NULL);

}

void *ft_strtok_quote_new(char *str)
{
    static t_str    s;
    bool    valid_flg;


    if (str != NULL)
	{
		while ((*(s.end) >= '\t' && *(s.end) <= '\r') || *(s.end) == ' ')
			str++;
		s.start = str;
	}
	else
		s.start = s.end + 1;
	if (*(s.start) == '\0') //CAUTION: don't consider metachar
	{
		*(s.start) = '\n';
		return (&s);
	}
    if (*(s.start) == '\"' || *(s.start) == '\'')
		s.end = valid_quotes(s.start, *(s.start));
    else
    {
        s.end = s.start;
        while (*(s.end) != '\'' && *(s.end) != '\"' && *(s.end) != '\0')
            s.end++;
    }
    return(&s);   //confuse: malloc안하고 지역변수로 선언해도 살아있던가..
}

int main()
{
	char s[] = "    grep \"a1 e\"";
    t_str *str;

	str = ft_strtok_quote_new(s);
    while (str != NULL && *(str->start) != '\'' && *(str->start) != '\"')
        str = ft_strtok_quote_new(s);
}