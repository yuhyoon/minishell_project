#ifndef EXECUTION_H
# define EXECUTION_H

# include "main.h"

//int		execute(t_minish *sh);

//redirect
int		valid_rdrct(t_ready *rdy);
int		redirect(t_list **rd_list, t_ready *rdy);
void	set_io(t_ready *rdy, t_stack *in, t_stack *out);
void	sort_io(t_stack *in, t_stack *out, t_ready *rdy);

//cmd
char	*get_acesspath(t_ready *rdy, int *pipe);
char	*find_exepath(char *name);
char	**create_str_2(t_list **head);
void	free_splited(char **abs);
#endif
