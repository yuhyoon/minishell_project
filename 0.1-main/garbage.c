void	maniplt_next(t_list **fst, int t)
{
	t_list	*tmp;
	t_redrct	*rd;
	t_list	*first;

	if (*fst == NULL)
		return ;
	first = *fst; 
	while (first)
	{
		rd = (t_redrct *)(first)->content;
		if (rd->type == t)
		{
			tmp = first;
			tmp = tmp->next;
		}
		(first) = (first)->next;
	}
}

void	init_first(t_list **in, t_list **out, t_list **rd_list)
{
	t_list		**tmp;
	t_redrct	*rd;

	tmp = rd_list;
	printf("\nrd_list\n");
	while (*tmp)
	{
		rd = (t_redrct *)(*tmp)->content;
		printf("%s\n", rd->obj);
		if (rd->type == IN_RD && *in == NULL)
		{
			*in = *tmp;
		}
		else if (rd->type == OUT_RD && *out == NULL)
		{
			*out = *tmp;
		}
		*tmp = (*tmp)->next;
	}
}

char    **create_str_2(t_list **head)
{
    int size;
    char    **str;
    t_list  *tmp;
	int	i;
    
	size = ft_lstsize(*head);
    str = malloc(sizeof(char *) * (size));
	i = 0;
	tmp = *head;
    while (i < size)
    {
        str[i] = ft_strdup((char *)tmp->content);
		i++;
		tmp = tmp->next;
    }
	ft_lstclear(head, del_text);
	return (str);
}

int	valid_io(t_list **rdy_head)
{
	t_list	*tmp;
	t_ready	*rdy;

	tmp = *rdy_head;
	rdy = ((t_ready *)(tmp->content));
	if (access(rdy->in->obj, R_OK) != 0)
		err_permission(1, rdy->in);
	if (access(rdy->out->obj, W_OK) != 0)
		err_permission(1, rdy->out);
	return (errno);
}