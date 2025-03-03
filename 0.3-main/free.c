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

void	free_minish(t_minish *minish)
{
    if (minish->src)
    {
        free(minish->src);
        minish->src = NULL;
    }
    if (minish->ready)
        ft_lstclear(&minish->ready, del_ready);
    free(minish->child_pids);
    minish->child_pids = NULL;
    //free_str_array(minish->envp);
    //exitcode = 0;
}
