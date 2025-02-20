#include "main.h"
#include "parse_main.h"

int execute_ready(t_minish *sh)
{
    t_ready *rdy;

    rdy = (t_ready *)(sh->ready->content);
    printf("execute\n");
    
}
