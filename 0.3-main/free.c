#include "main.h"

void	free_str_array(char **arr)
{
	int i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	dengling(void *content, int size_type)
{
	if (size_type == 1)
		free((char *)content);
	if (size_type == 4)
		free((pid_t *)content);
	content = NULL;
}

// void	safe_free(void **ptr)
// {
// 	if (ptr && *ptr)
// 	{
// 		free(*ptr);
// 		*ptr = NULL;
// 	}
// }

void	free_envps(t_envp **node)
{
	t_envp	*current;
	t_envp	*next;

	if (!node || !*node)
		return;
	current = *node;
	while (current)
	{
		next = current->next;
		// if (current->o_envp)
		// {
		// 	i = 0;
		// 	while (current->o_envp[i])
		// 		free(current->o_envp[i++]);
		// 	free(current->o_envp);
		// }
		if (current->key)
		{
			free(current->key);
			current->key = NULL;
		}
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
	*node = NULL;
}

void	free_minish(t_minish *minish)
{
	// t_list	**head;
	// t_list	*current;
	// t_ready	*ready_content;

	if (minish->mask)
		dengling(minish->mask, 1);
	if (minish->src)
		dengling(minish->src, 1);
	// if (minish->ready)
	// {
	// 	ft_lstclear(&minish->ready, del_ready);
	// 	current = minish->ready;
	// 	while (current)
	// 	{
	// 		ready_content = (t_ready *)(current->content);
	// 		if (ready_content && ready_content->text)
	// 			ft_lstclear(&(ready_content->text), del_text);
	// 		current = current->next;
	// 	}
	// 	ft_lstclear(&minish->ready, del_ready);
	// }
    if (minish->ready)
		ft_lstclear(&minish->ready, del_ready);
	if (minish->child_pids)
		dengling(minish->child_pids, 4);
	minish->prev_for_pipe = -1;
	// ft_memset(minish, 0, sizeof(t_minish));
}
