#include "main.h"
#include "parse_main.h"

int execute_ready(t_minish *sh)
{
    t_list  *rdy_list;
    t_ready *rdy;

    rdy_list = sh->ready;
    rdy = (t_ready *)(sh->ready->content);
    printf("execute\n");
    
}
