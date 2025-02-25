#include "parse_main.h"
# include "token_step-1_utils.h"
#include "create_ready.c"
#include "execute_meta.c"
#include "stack.h"
#include "token_step-2_utils.c"


t_list *init_parsing_structure(t_list **rdy_head)
{
    t_ready *rdy;

	rdy = create_rdy();
    ft_lstadd_back(rdy_head, ft_lstnew(rdy));
    return (rdy_head);
}

t_list	*init_rdrct(void)
{
	t_redrct	*rdrct;

	rdrct = malloc(sizeof(t_redrct));
	ft_memset(rdrct, 0, sieof(rdrct));
	return (rdrct)
}

int	handle_pipe(t_minish *sh, t_ready *current_rdy,  t_list **rdrct, int save)
{
	t_ready	*next_rdy;
	t_list	*next_lst;

	//redirect(rdrct, current_rdy);
	if (*rdrct != NULL)
		current_rdy->rdrct_num = ft_lstsize(*rdrct);
	create_text(current_rdy, &sh->src[save], &sh->mask[save], sh);
	next_rdy = create_rdy();
	next_lst = ft_lstnew(next_rdy);
	ft_lstadd_back(&sh->ready, next_lst);
	return (1);
}

void *parsing(t_minish *sh, int len)
{
	int		i;
	t_ready	*rdy;
	int	save;

	i = 0;
	save = i;
	init_parsing_structure(&sh->ready);
	rdy = ((t_ready *)sh->ready->content);
	while (i < len && exitcode == 0)
	{
		if (sh->mask[i] == IN_RD || sh->mask[i] == OUT_RD)
			i += create_rdrct(&sh->src[i], &sh->mask[i], &rdy->rdrct);
		else if (sh->mask[i] == PIPE)
		{
			i += handle_pipe(sh, rdy, &rdy->rdrct, save);
			save = i;
		}
		else
			i++;
	}
	if (save == 0)
	{
		if (rdy->rdrct != NULL)
			current_rdy->rdrct_num = ft_lstsize(*rdrct);
		create_text(rdy, &sh->src[save], &sh->mask[save], sh);
	}
	return (sh->ready);
}
