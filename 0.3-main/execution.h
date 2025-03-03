#ifndef EXECUTION_H
# define EXECUTION_H

# include "main.h"

int		execute(t_minish *sh);
int		redirect(t_list **rd_list, t_ready *rdy);
void	set_io(t_ready *rdy, t_stack *in, t_stack *out);
void	sort_io(t_stack *in, t_stack *out, t_ready *rdy);

#endif