#include "parse_main.h"
# include "token_step-1_utils.h"
#include "delete.h"

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
	return (exitcode);
}
