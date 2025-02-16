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
int	create_meta(char *src, char *mask, t_ready **rdy)
{
	int	i;
	t_list	*io;
	t_list	*dolar;

	i = 0;
	if (mask[i] <= 1)
	{
		i++;	
	}
	else if (mask[i] == IN_RD || mask[i] == OUT_RD)
	{
		i += create_io(src, mask, mask[i], rdy);
	}
	else if (mask[i] == DOLLAR)
	{
		i += create_dolar(src, mask, rdy);
	}
	return (i);
}

int	execute_meta(t_ready **rdy)
{
	while (((*rdy)->io) != NULL)
	{
		//ft_lstclear(&(*rdy)->io, execute_rd());
	}
	while (((*rdy)->dolar) != NULL)
	{
		//ft_lstclear(&(*rdy)->dolar, execute_rd());
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

void	*create_exeinfo(t_ready *rdy, char *src, char *mask)
{
	t_exe_info	*exe;

	exe = malloc(sizeof(exe));
	exe->cmd = create_str_2(&(rdy->text));
	return (exe);
}


void *parsing(char *src, char *mask, int len)
{
	int		i;
	t_ready	*rdy;
	t_list	*rdy_head;
	t_list	*new;
	int	save;

	rdy = create_rdy();
	i = 0;
	save = i;
	rdy_head = NULL;
	new = ft_lstnew(rdy);
	ft_lstadd_back(&rdy_head, new);
	while (i < len)
	{
		i += create_meta(src, mask, &rdy);
		if (mask[i] == PIPE)
		{
			execute_meta(&rdy);
			create_text(rdy, &src[save], &mask[save]);
			rdy = create_rdy();
			new = ft_lstnew(rdy);
			ft_lstadd_back(&rdy_head, new);
			i++;
			save = i;
		}
	}
	execute_meta(&rdy);
	create_text(rdy, &src[save], &mask[save]);
	//clean_ready(&rdy);
	
	return (rdy_head);
}
