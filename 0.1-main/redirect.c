#include "parse_main.h"
# include "token_step-1_utils.h"
#include "stack.h"
#include "delete.h"

void	sort_io(t_stack *in, t_stack *out, t_list **rd_list)
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

void	set_io(t_ready *rdy, t_stack *in, t_stack *out)
{
	(rdy)->in = (t_redrct *)pop2(in);
	(rdy)->out = (t_redrct *)pop2(out);
}

int	redirect(t_list **rd_list, t_ready *rdy)
{
	t_stack	in;
	t_stack out;

	// if (valid_access(rd_list) != 0)
	// 	return (-1);
	init_stack(&in, NULL, 0);
	init_stack(&out, NULL, 0);
	sort_io(&in, &out, rd_list);
	set_io(rdy, &in, &out);
	set_io(rdy, &in, &out);
	del_stack(&in);
	del_stack(&out);
	//todo: clear_stack
	//ft_lstclear(&(*rdy)->io, execute_rd());
}
