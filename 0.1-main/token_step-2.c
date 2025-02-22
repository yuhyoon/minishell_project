#include "parse_main.h"
# include "token_step-1_utils.h"
#include "create_ready.c"
#include "execute_meta.c"
#include "stack.h"
#include "token_step-2_utils.c"

void	divide_io(t_stack *in, t_stack *out, t_list **rd_list)
{
	t_list		**tmp;
	t_redrct	*rd;

	tmp = rd_list;
	while (*tmp)
	{
		rd = (t_redrct *)(*tmp)->content;
		if (rd->type == IN_RD)
			push(in, rd);
		else if (rd->type == OUT_RD)
			push(out, rd);
		*tmp = (*tmp)->next;
	}
}

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


void	set_io(t_ready *rdy, t_stack *in, t_stack *out)
{
	(rdy)->in = (t_redrct *)pop2(in);
	(rdy)->out = (t_redrct *)pop2(out);
}

int	divide_rdrct(t_list **rd_list, t_ready *rdy)
{
	t_stack	in;
	t_stack out;

	init_stack(&in, NULL, 0);
	init_stack(&out, NULL, 0);
	divide_io(&in, &out, rd_list);
	set_io(rdy, &in, &out);
	set_io(rdy, &in, &out);
	//todo: clear_stack
	//ft_lstclear(&(*rdy)->io, execute_rd());
}

/* *
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
*/

t_list *init_parsing_structure(void)
{
    t_ready *rdy;
    t_list *rdy_head;
    t_list *new;

	rdy = create_rdy();
	rdy_head = NULL;
	new = ft_lstnew(rdy);
    ft_lstadd_back(&rdy_head, new);
    return (rdy_head);
}

int	handle_pipe(t_minish *sh, t_ready *current_rdy,  t_list **rdrct, int save)
{
	t_ready	*next_rdy;
	t_list	*next_lst;

	if (valid_access(rdrct) != 0)
		return (-1);
	divide_rdrct(rdrct, current_rdy);
	create_text(current_rdy, &sh->src[save], &sh->mask[save]);
	next_rdy = create_rdy();
	next_lst = ft_lstnew(next_rdy);
	//print error
	ft_lstadd_back(&sh->ready, next_lst);
	return (1);
}

void *parsing(t_minish *sh, int len)
{
	int		i;
	t_ready	*rdy;
	t_list	*rdy_head;
	int	save;
	t_list  *rdrct;

	i = 0;
	save = i;
	rdrct = NULL;
	sh->ready = init_parsing_structure();
	rdy = ((t_ready *)rdy_head->content);
	while (i < len && exitcode == 0)
	{
		if (sh->mask[i] == IN_RD || sh->mask[i] == OUT_RD)
			i += create_rdrct(&sh->src[i], &sh->mask[i], &rdrct);
		else if (sh->mask[i] == PIPE)
		{
			i += handle_pipe(sh, rdy,  &rdrct, save);
			save = i;
		}
		else
			i++;
	}
	if (save == 0)
	{/*
		//todo:seperate
		if (valid_access(rdrct) != 0)
		return (NULL);
	divide_rdrct(&rdrct, rdy);
	create_text(rdy, &src[save], &mask[save]);
	*/
	}
	return (rdy_head);
}
