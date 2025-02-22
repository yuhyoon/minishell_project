#ifndef STACK_H
# define STACK_H
# include "parse_main.h"

void	init_stack(t_stack *stack, void *top, int size);
int		is_emthy(t_stack *stack);
void    push(t_stack *stack, void *data);
int pop(t_stack *stack);
void *pop2(t_stack *stack);

# endif
