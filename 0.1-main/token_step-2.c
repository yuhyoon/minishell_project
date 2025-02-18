#include "parse_main.h"
# include "token_step-1_utils.h"
#include "create_ready.c"
#include "execute_meta.c"

void	del_text(void *txt)
{
	free((char *)txt);
	txt = NULL;
}

void	del_redrct(t_redrct *redrct)
{
	free(redrct->obj);
	redrct->obj = NULL;
}

void	del_dollar(t_dollar *dolr)
{
	free(dolr->str);
	dolr->str = NULL;
}

void	clean_ready(t_ready **rdy)
{
	ft_lstclear(&(*rdy)->text, del_text);
//	ft_lstclear((*rdy)->io, del_redrct((*rdy)->io->content));
//	ft_lstclear((*rdy)->dolar, del_dollar((*rdy)->dolar->content));

}

//return length
int	f(char *src, char *mask, t_list **io)
{
	int	i;
	t_list	*io;

	i = 0;
	if (mask[i] == IN_RD || mask[i] == OUT_RD)
	{
		i += create_io(src, mask, mask[i], io);
	}
	else
		i++;
	return (i);
}

void	init_first(t_list **in, t_list **out, t_list **rd_list)
{
	t_list		**tmp;
	t_redrct	*rd;

	tmp = rd_list;
	while (*tmp)
	{
		rd = (t_redrct *)(*tmp)->content;
		if (rd->type == IN_RD && *in == NULL)
		{
			*in = rd;
		}
		else if (rd->type == OUT_RD && *out == NULL)
		{
			*out = rd;
		}
		tmp = tmp->next;
	}
}

void	maniplt_next(t_list **first, int t)
{
	t_list	*tmp;
	t_redrct	*rd;
	t_list	**first_backup;

	first_backup = first; 
	rd = (t_redrct *)(*first)->content;
	while (*first)
	{
		if (rd->type == t)
		{
			tmp = *first;
			tmp = tmp->next;
		}
		(*first) = (*first)->next;
	}
	return (first_backup);
}

int	divide_rdrct(t_list **rd_list)
{
	t_list	*in;
	t_list	*out;

	in = NULL;
	out = NULL;
	init_first(&in, &out, rd_list);
	maniplt_next(&in, IN_RD);
	maniplt_next(&out, OUT_RD);
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

void	*create_exeinfo(t_ready *rdy, char *src, char *mask)
{
	t_exe_info	*exe;

	exe = malloc(sizeof(exe));
	exe->cmd = create_str_2(&(rdy->text));
	return (exe);
}
*/

void *parsing(char *src, char *mask, int len)
{
	int		i;
	t_ready	*rdy;
	t_list	*rdy_head;
	t_list	*new;
	int	save;
	t_list  *rdrct;

	rdy = create_rdy();
	i = 0;
	save = i;
	rdy_head = NULL;
	new = ft_lstnew(rdy);
	ft_lstadd_back(&rdy_head, new);
	while (i < len)
	{
		i += f(src, mask, &rdrct);
		if (mask[i] == PIPE)
		{
			divide_rdrct(&rdrct);
			create_text(rdy, &src[save], &mask[save]);
			rdy = create_rdy();
			new = ft_lstnew(rdy);
			ft_lstadd_back(&rdy_head, new);
			i++;
			save = i;
		}
	}
	divide_rdrct(&rdrct);
	create_text(rdy, &src[save], &mask[save]);
	//clean_ready(&rdy);
	
	return (rdy_head);
}
