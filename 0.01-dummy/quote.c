
#include "dummy_main.h"
#include <stdbool.h>
#include "parse_main.h"
#include <string.h>

typedef struct s_argp
{
	int argc;
	char **argv;
	char *envp;
	int		dollar;
} t_argp;

int	ft_strlen_delim(char *s, char delim)
{
	int i;

	i = 0;
	while (s[i] != delim)
	{
		i++;
	}
	return (i);
}

char *ft_strtok_quote(char *str, t_argp *argp)
{
	static char *start;
	static char *end;
	bool is_quote;
	char *token;
	int		dollar_cnt;;

	is_quote = false;
	dollar_cnt = 0;
	if (str != NULL)
	{
		while ((*end >= '\t' && *end <= '\r') || *end == ' ')
			str++;
		start = str;
	}
	else
		start = end + 1;
	if (*start == '\0') //CAUTION: don't consider metachar
	{
		*start = '\n';
		return (start);
	}
	if (*start == '\"' || *start == '\'')
		is_quote = true;
	if (is_quote == true)
	{
		if (*start == '\"')
		{
			end = start + 1;
			while (*end != '\"' && *end != '\0')
			{
				if (*end == '$')//TODO: store the address of dollar
					dollar_cnt++;
				end++;
			}
			if (*end == '\"')
			{
				*start = '\0';
				*end = '\0';
				argp->dollar = dollar_cnt;
			}
			else if (*end == '\0')
			{
				argp->dollar = 0;
			}
		}
	}
	else if (is_quote == false)
	{
		end = start;
		while (*end != '\"' && *end != '\0')
			end++;
		*end = '\0';
	}
	return (start);
}

void *init_argp(t_argp *argp, char *s)
{

	char **argv;
	char *p;
	int cnt;

	cnt = 0;
	p = ft_strtok_quote(s, argp);
	while (p != NULL && *p != '\n')
	{
		printf("%s\n", p);
		cnt++;
		p = ft_strtok_quote(NULL, argp);
	}
	if (p == NULL)
	{
		free(s);
		s = NULL;
	}
	return (s);
}

int create_argp(char *input, t_lex *lex)
{
	t_argp *argp;
	char	*maniplte;
	char	*tmp;

	lex->tkn_type = 1;
	argp = malloc(sizeof(t_argp));
	maniplte = strdup(input);
	init_argp(argp, maniplte);
	if (maniplte == NULL)
		return (-1);
	printf("%s", maniplte);
	return (ft_strlen_delim(maniplte, '\n'));
}

//main for test
int main()
{
	char s[] = "    grep \"a1 e\"";
	t_lex lex;

	int n = create_argp(s, &lex);
	if (n == -1)
		printf("Unclosed quotes!\n");
	else
		printf("length: %d\n", n);
}