#include "parse_main.h"

void    *create_rdy()
{
    t_ready *rdy;

    rdy = malloc(sizeof(t_ready));
    rdy->text = NULL;
    rdy->io = NULL;
    rdy->dolar = NULL;
    rdy->next = NULL;
    return (rdy);
}

int	create_dolar(char *src, char *mask, t_ready *rdy)
{

}

int create_io(char *src, char *mask, int rd, t_ready **head)
{
    int i;
	t_redrct	*new;
	char	*str;
	int		len;

    i = 0;
    while (mask[i] == rd)
        i++;
    if (i >= 3)
    {
		//todo: error handling
    }
	new = malloc(sizeof(t_redrct));
	new->type = *mask;
	new->parts = i;
    while(mask[i] == 0)
		i++;
	len = ft_strlen(&mask[i]);
	ft_memset(&mask[i], rd, len);
	str = malloc(sizeof(char) * (len + 1));
	str = ft_memcpy(str, &src[i], len);
	str[len] = '\0';
	new->obj = str;
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

// int	create_text_4()
// {

// }

void    create_text(t_ready *rdy, char *src, char *mask)
{
    int i;
    t_str   str_info;
    t_list  *head;
    t_list  *lst;
    char    *r;
    int n;

    i = 0;
    str_info.src = src;
    head = NULL;
    while (mask[i] != '\n' && mask[i] != PIPE)
    {
		if (mask[i] == 0)
			i++;
    	else if (mask[i] == 1)
        {
            i += create_text_1(&mask[i], "1", &src[i], &head);
		}
		else if (mask[i] == 4)
		{
			//i += create_text_4();
		}
    }
	rdy->text = head;   
}

