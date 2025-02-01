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
		while ((*str >= '\t' && *str <= '\r') || *str == ' ')
			str++;
		s.start = str;
	}
    else if (*(s.end) == '\0')
        return (NULL);

	s.start = s.end + 1;
    s.end = s.start;
	while (*(s.end) != '\'' && *(s.end) != '\"' && *(s.end) != '\0' && !(*str >= '\t' && *str <= '\r') && *str != ' ')
        s.end++;
    
    return(&s);   //confuse: malloc안하고 지역변수로 선언해도 살아있던가..
}

int main()
{
	char s[] = "    grep \"a1 e\"";
    t_str *str;
	int	fd;
	char	*valid_quotes_flg;

	str = ft_strtok_quote_new(s);
	fd = open("valid_pthes", O_RDWR | O_CREAT | O_TRUNC, 0644);
    while (str != NULL && *(str->end) != '\'' && *(str->end) != '\"')
    {
        write(fd, str->start, str->end - str->start - 1);
		write(fd, "\n", 1);
		str = ft_strtok_quote_new(NULL);
    }
	if (*(str->end) != '\'' || *(str->end) != '\"')
		valid_quotes_flg = valid_quotes(str->end, *(str->end));
	if (*(valid_quotes_flg) == '\'' || *(valid_quotes_flg) == '\"' )
		//todo:ft_strtok_quote_new에 매개변수 추가
		//ft_strtok_quote_new(s, *valid_quotes_flg)
}