#include "parse_main.h"
#include "delete.h"

void    *create_rdy()
{
    t_ready *rdy;
	static	int	num; //study: 폴더 최대 몇개까지 만들 수 있는지 

    rdy = malloc(sizeof(t_ready));
    rdy->text = NULL;
    rdy->rdrct = NULL;
    rdy->in = NULL;
    rdy->out = NULL;
    return (rdy);
}

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

//todo: < a 나 > b 에서 실행파일도 리디렉션 적용되는지 확인
int	access_file(t_redrct *rdrct)
{
	int	mode;

	if (rdrct->type == IN_RD && rdrct->parts == 2)
		mode = 0;//todo: here_doc(rdrct);
	else if (rdrct->type == OUT_RD && rdrct->parts == 1)
		mode = access(rdrct->obj, W_OK);
	else if (rdrct->type == IN_RD && rdrct->parts == 1)
		mode = access(rdrct->obj, R_OK);
	rdrct->access = mode;
}

int create_rdrct(char *src, char *mask, t_list **head)
{
    int i;
	t_redrct	*new;
	char	*str;
	int		len;
	t_list	*lst;

    i = 0;
	new = malloc(sizeof(t_redrct));
	new->type = mask[i];
    while (mask[i] == new->type)
        i++;
	new->parts = i;
	while (mask[i] == NONE)
		i++;
	len = count_text(&mask[i]);
	ft_memset(&mask[i], new->type, len);
	str = malloc(sizeof(char) * (len + 1));
	str = ft_memcpy(str, &src[i], len);
	str[len] = '\0';
	new->obj = str;
	//access_file(new);
	lst = ft_lstnew(new);
	ft_lstadd_back(head, lst);
	return (i + len);
}

int create_text_1(char *s1, char *s2, char *src, t_list **head)
{
    int i;
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

char	*valid_env(char *tmp)
{
	char	*env;

	env = getenv(tmp);
	if (env == NULL)
	{
		env = malloc(sizeof(char));
		*env = '\0';
		if (*tmp == '?')
		{
			free(env);
			env = ft_strjoin("$", tmp);
		}
	}
	else
		env = ft_strdup(env);
	return (env);
}

int	create_text_4(char *mask, char *src, t_list **head)
{
	int	i;
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

void    create_text(t_ready *rdy, char *src, char *mask, t_minish *sh)
{
    int i;
    t_list  *head;
    t_list  *lst;

	if (rdy->rdrct == NULL)
	{
		printf("what the\n");
	//	ft_lstclear(&sh->ready, del_ready);
		return ;
	}
    i = 0;
    head = NULL;
    while (mask[i] != '\n' && mask[i] != PIPE )
    {
    	if (mask[i] == 1)
            i += create_text_1(&mask[i], "1", &src[i], &head);
		else if (mask[i] == 4)
			i += create_text_4(&mask[i], &src[i], &head);
		else
			i++;
    }
	rdy->text = head;   
}

