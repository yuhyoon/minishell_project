#include "main.h"
#include "parse_main.h"

void    err_such(int exit, t_redrct *rdrct)
{
    char *obj;

    exitcode = exit;
    obj = rdrct->obj;
    printf("minish: %s: No such file or directory\n", rdrct->obj);
}

void    err_permission(int exit, t_redrct *rdrct)
{
	char *obj;

    exitcode = exit;
    obj = rdrct->obj;
    printf("minish: %s: Permission denied\n", rdrct->obj);
}