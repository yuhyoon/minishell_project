#include "main.h"
#include "parse.h"
#include "analysis.h"
#include "parse_step.h"

void	*create_rdy()
{
	t_ready *rdy;

	rdy = malloc(sizeof(t_ready));
	ft_memset(rdy, 0, sizeof(t_ready));
	return (rdy);
}

t_list *init_parsing_structure(t_list **rdy_head)
{
	t_ready *rdy;

	rdy = create_rdy();
	ft_lstadd_back(rdy_head, ft_lstnew(rdy));
	return (*rdy_head);
}

int	handle_pipe(t_list **lst, t_ready *current_rdy,  t_list **rdrct, int save)
{
	t_ready	*next_rdy;
	t_list	*next_lst;

	if (*rdrct != NULL)
		current_rdy->rdrct_num = ft_lstsize(*rdrct);
	create_text_list(current_rdy, current_rdy->line[save], current_rdy->mask[save]);
	next_rdy = create_rdy();
	next_lst = ft_lstnew(next_rdy);
	ft_lstadd_back(lst, next_lst);
	return (1);
}

void *parsing(const t_list *cur_rdylst, int len)
{
	int		i;
	t_ready	*rdy;
	int		save;
	t_list	*lst;

	i = 0;
	save = i;
	lst = (t_list *)cur_rdylst;
	while (i < len)
	{
		rdy = ((t_ready *)lst->content);
		if (rdy->mask[i] == IN_RD || rdy->mask[i] == OUT_RD)
			i += create_rdrct(&rdy->src[i], &rdy->mask[i], &rdy->rdrct);
		else if (rdy->mask[i] == PIPE)
		{
			i += handle_pipe(&lst, rdy, &rdy->rdrct, save);
			lst = lst->next;
			save = i;
		}
		else
			i++;
	}
	if (rdy->rdrct != NULL)
		rdy->rdrct_num = ft_lstsize(rdy->rdrct);
	create_text_list(rdy, &rdy->src[save], &rdy->mask[save]);
	return (lst);
}
