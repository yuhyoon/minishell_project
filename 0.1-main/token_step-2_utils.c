#include "parse_main.h"
# include "token_step-1_utils.h"

void	del_text(char *txt)
{
	free(txt);
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
}

int valid_access(t_list **head)
{
    t_list  *tmp;
	t_redrct	*rd;

	tmp = *head;
	while (tmp && exitcode == 0)
	{
		rd = (t_redrct *)tmp->content;
		if (rd->access != 0)
			exitcode = 1;
		tmp = tmp->next;
	}
	if (exitcode != 0)
		ft_lstclear(head, del_redrct);
	return (exitcode);
}