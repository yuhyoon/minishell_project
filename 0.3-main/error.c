#include "main.h"
#include "parse.h"

void    err_such(int exit, t_redrct *rdrct)
{
    char *obj;

    exitcode = exit;
    obj = rdrct->obj;
	write(2, "minish: ", 8);
	write(2, obj, ft_strlen(obj));
	write(2, ": ", 2);
    write(2, "No such file or directory\n", 25);
}

void    err_permission(int exit, t_redrct *rdrct)
{
	char *obj;

    exitcode = exit;
    obj = rdrct->obj;
	write(2, "minish: ", 8);
	write(2, obj, ft_strlen(obj));
	write(2, ": ", 2);
    write(2, "Permission denied\n", 17);
}
void    err_exec(int exit, char *cmd_name)
{
	exitcode = exit;
	write(2, "minish: ", 8);
	write(2, cmd_name, (unsigned int)ft_strlen(cmd_name));
	write(2, ": command not found\n", 20);
}

void	err_syntax(int syntax_result)
{
	if (syntax_result == 0)
		return ;
	write(2, "minish: ", 8);
	if (syntax_result == 1)
		write(2, "syntax error!\n", 14);
	else if (syntax_result == 2)
		write(2, "syntax error! minishell don't support.\n", 39);
	
}
