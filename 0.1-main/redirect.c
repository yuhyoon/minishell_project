#include "parse_main.h"
# include "token_step-1_utils.h"
#include "stack.h"
#include "delete.h"

void	sort_io(t_stack *in, t_stack *out, t_ready *rdy)
{
	t_list		*tmp;
	t_redrct	*rd;
	int			n;

	n = rdy->rdrct_num;
	tmp = rdy->rdrct;
	while (n)
	{
		rd = (t_redrct *)(tmp)->content;
		if (rd->type == IN_RD)
			push(in, rd);
		else if (rd->type == OUT_RD)
			push(out, rd);
		n--;
		tmp = (tmp)->next;
	}
}

void	set_io(t_ready *rdy, t_stack *in, t_stack *out)
{
	(rdy)->in = (t_redrct *)pop2(in);
	rdy->in->fd = open(rdy->in->obj, O_RDONLY);
	(rdy)->out = (t_redrct *)pop2(out);
	if (rdy->out->parts == 1)
		rdy->out->fd = open(rdy->out->obj, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	else if (rdy->out->parts == 2)
		rdy->out->fd = open(rdy->out->obj, O_APPEND | O_WRONLY | O_CREAT, 0644);
}

int	redirect(t_list **rd_list, t_ready *rdy)
{
	t_stack	in;
	t_stack out;

	if (valid_rdrct(rdy) != 0)
		return (-1);
	init_stack(&in, NULL, 0);
	init_stack(&out, NULL, 0);
	sort_io(&in, &out, rdy);
	set_io(rdy, &in, &out);
	set_io(rdy, &in, &out);
	del_stack(&in);
	del_stack(&out);
	return (0);	
}
