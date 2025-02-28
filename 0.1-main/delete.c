#include "delete.h"

void	del_text(void *txt)
{
	free((char *)txt);
	txt = NULL;
}

void	del_redrct(void *rd)
{
	t_redrct *redrct;

	redrct = rd;
	if (redrct == NULL)
		return ;
	free(redrct->obj);
	redrct->obj = NULL;
}

void	del_ready(void *ready)
{
	t_ready	*rdy;

	rdy = ready;
	ft_lstclear(&rdy->text, del_text);
	ft_lstclear(&rdy->rdrct, del_redrct);
	del_redrct(rdy->rdrct_in);
	del_redrct(rdy->rdrct_out);
}

void	del_stack(void *st)
{
	t_stack	*stack;

	stack = st;
	if (stack == NULL)
		return ;
	while (!is_emthy(stack))
		pop2(stack);
	stack = NULL;
}
