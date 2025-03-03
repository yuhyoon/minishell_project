#include "parse.h"

void	init_stack(t_stack *stack, void *top, int size)
{
	stack->top = NULL;
	stack->size = 0;
}

int		is_emthy(t_stack *stack)
{
	if (stack->top == NULL)
		return (true);
	else
		return (false);
}

void    push(t_stack *stack, void *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = data;
	new->next = stack->top;
	stack->top = new;
	stack->size++;
}

int pop(t_stack *stack)
{
    t_list  *tmp;
    char     *value;

    tmp = stack->top;
    value = tmp->content;
    stack->top = tmp->next;
	free(tmp);
	stack->size--;
	return (0);
}

void	*pop2(t_stack *stack)
{
	t_list	*tmp;
	void	*content;

	if (is_emthy(stack))
		return (NULL);
	tmp = stack->top;
	content = tmp->content;
	stack->top = tmp->next;
	free(tmp);
	stack->size--;
	return (content);
}

void	*peek_rd(t_stack *stack)
{
	if (is_emthy(stack))
		return (NULL);
	return ((t_redrct *)(stack->top->content));
}
