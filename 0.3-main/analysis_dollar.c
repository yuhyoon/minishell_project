#include "analysis.h"

int	count_text(char *mask)
{
	int	i;

	i = 0;
	while (mask[i] != PIPE && mask[i] != '\n' && mask[i] != NONE)
	{
		i++;
	}
	return (i);
}

char	*valid_env(char *tmp)
{
	char	*env;

	env = getenv(tmp);
	if (env == NULL)
	{
		env = malloc(sizeof(char));
		*env = '\0';
		if (*tmp == '?') //todo: exitcode로 변경 
		{
			free(env);
			env = ft_itoa(exitcode);
		}
	}
	else
		env = ft_strdup(env);
	return (env);
}

int get_plain_text(char *s1, char *s2, char *src, t_list **head)
{
    int		i;
	char	*rsult;
	t_list	*new;

    i = 0;
	while (s1[i] == (*s2 - '0'))
		i++;
	rsult = malloc(sizeof(char) * (i + 1));
	ft_memcpy(rsult, src, i);
	rsult[i] = '\0';
	new = ft_lstnew(rsult);
	ft_lstadd_back(head, new);
    return (i);
}

int	get_variable(char *mask, char *src, t_list **head)
{
	int		i;
	char	*rsult;
	char	*tmp;
	t_list	*new;

	i = 0;
	i++;
	while (mask[i] == 1)
		i++;
	tmp = ft_substr(&src[i - (i - 1)], 0, i - 1); //$HOME| 처럼 뒤에 바로 파이프가 올수도있으니까..
	rsult = valid_env(tmp); //널반환하는지 확인
	new = ft_lstnew(rsult);
	ft_lstadd_back(head, new);
	free(tmp);
	return (i);
}
void    create_text_list(t_ready *rdy, char *src, char *mask, t_minish *sh)
{
    int 	i;
    t_list  *head;
	(void)	sh;

    i = 0;
    head = NULL;
    while (mask[i] != '\n' && mask[i] != PIPE)
    {
    	if (mask[i] == 1)
            i += get_plain_text(&mask[i], "1", &src[i], &head);
		else if (mask[i] == 4)
			i += get_variable(&mask[i], &src[i], &head);
		else
			i++;
    }
	rdy->text = head;
}
