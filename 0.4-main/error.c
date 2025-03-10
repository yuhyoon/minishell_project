#include "main.h"
#include "parse.h"

//todo: 에러메시지 fd2에 작성하기
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
void    err_exec(int exit, char *cmd_name)
{
	exitcode = exit;
	write(2, "minish: ", 8);
	write(2, cmd_name, (unsigned int)ft_strlen(cmd_name));
	write(2, ": command not found\n", 18);
}

void    err_syntax(t_minish *sh)
{
	write(2, "minish: ", 8);
	write(2, "syntax error\n", 13);
    //todo: bash랑 똑같이 메시지해야할지?
    sh->last_exit = 2;
}