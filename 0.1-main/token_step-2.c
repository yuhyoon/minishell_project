#include "parse_main.h"
# include "token_step-1_utils.h"
#include "create_ready.c"
#include "execute_meta.c"
#include "stack.h"
#include "token_step-2_utils.c"
#include "redirect.c"

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

	redirect(rdrct, current_rdy);
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
	t_list  *rdrct;

	i = 0;
	save = i;
	rdrct = NULL;
	sh->ready = init_parsing_structure();
	rdy = ((t_ready *)sh->ready->content);
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
	{
		redirect(&rdrct, rdy);
		create_text(rdy, &sh->src[save], &sh->mask[save], sh);
	}
	return (sh->ready);
}
