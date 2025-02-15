#include "parse_main.h"

void    *create_rdy(t_ready *head)
{
    t_ready *rdy;

    rdy = malloc(sizeof(t_ready));
    rdy->text = NULL;
    rdy->io = NULL;
    rdy->dolar = NULL;
    rdy->next = NULL;
    return (rdy);
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

void    create_text(t_ready *rdy, t_exe_info **head, char *src, char *mask)
{
    int i;
    t_str   str_info;
    t_list  **head;
    t_list  *lst;
    char    *r;

    i = 0;
    str_info.src = src;
    *head = NULL;
    while (mask[i] != '\n')
    {
        str_info.start = ft_strcspn(&src[i], "02345");
        str_info.end = ft_strspn(str_info.start, "1");
        r = malloc(sizeof(char) * ((str_info.end) - (str_info.start) + 1));
        ft_memset(r, 0, ((str_info.end) - (str_info.start) + 1));
        ft_memcpy(r, &mask[str_info.start], (str_info.end) - (str_info.start));
        lst = ft_lstnew(r);
        ft_lstadd_back(head, lst);
        i += str_info.end;
    }
    
}

