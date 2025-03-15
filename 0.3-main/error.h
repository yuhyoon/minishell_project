#include "main.h"
#include "parse.h"

void    err_such(int exit, t_redrct *rdrct);
void    err_permission(int exit, t_redrct *rdrct);
void    err_exec(int exit, char *cmd_name);
void	err_syntax(int syntax_result);
