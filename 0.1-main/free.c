#include "main.h"
#include "parse_main.h"
#include "delete.h"

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



static void	free_pipe(t_pipe *pipe)
{
    if (!pipe)
        return ;
    if (pipe->read_fd)
    {
        free(pipe->read_fd);
        pipe->read_fd = NULL;
    }
    if (pipe->write_fd)
    {
        free(pipe->write_fd);
        pipe->write_fd = NULL;
    }
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
    free_pipe(&minish->old_pipe);
    free_pipe(&minish->new_pipe);
    //free_str_array(minish->envp);
}
