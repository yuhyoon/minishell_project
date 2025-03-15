#include "main.h"


static void	free_str_array(char **arr)
{
    int	i;

    if (!arr)
        return ;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        arr[i] = NULL;
        i++;
    }
    free(arr);
}

void    dengling(void *content, int size_type)
{
	if (size_type == 1)
		free((char *)content);
	if (size_type == 4)
		free((int *)content);
	content = NULL;
}

void	free_minish(t_minish *minish)
{
    if (minish->mask)
		dengling(minish->mask, 1);
    if (minish->src)
		dengling(minish->src, 1);
    if (minish->ready)
        ft_lstclear(&minish->ready, del_ready);
	if (minish->child_pids)
		dengling(minish->child_pids, 4);
	ft_memset(minish, 0, sizeof(t_minish));
	minish->prev_for_pipe = -1;
	//free_str_array(minish->envp);
    //exitcode = 0;
}
