#include "parse_main.h"
# include "token_step-1_utils.h"

void	del_text(void *txt)
{
	free((char *)txt);
	txt = NULL;
}

void	del_redrct(void *rd)
{
	t_redrct *redrct;

	redrct = rd;
	free(redrct->obj);
	redrct->obj = NULL;
}

void	del_ready(void *ready)
{
	t_ready	*rdy;

	rdy = ready;
	ft_lstclear(&rdy->text, del_text);
	ft_lstclear(&rdy->rdrct, del_redrct);
	del_redrct(rdy->in);
	del_redrct(rdy->out);
}
