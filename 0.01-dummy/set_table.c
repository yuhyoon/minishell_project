#include "main_include.h"
#include "parse_main.h"
#include "table.h"

//todo: uncorrect rdirect->obj. correct is rdirect->type
t_redrct	*set_rediret(char *input)
{
	t_redrct	*rdirct;

	rdirct = malloc(sizeof(t_redrct));
	if (*input == '<' && *(input + 1) == '<')
		rdirct->obj = 2;
	else if (*input == '>' && *(input + 1) == '<')
		rdirct->obj = 3;
	else if (*input == '<')
		rdirct->obj = 0;
	else if (*input == '>')
		rdirct->obj = 1;
	if (rdirct->obj <= 1)
		input++;
	else if (rdirct->obj <= 3)
		input = input + 2;
	else
		return (NULL);
	//todo: rdirct->type = set_obj(redirect, input);
}

t_cmd	*create_cmd(char *input)
{
	char	*exe_path;
	t_cmd	*cmd;

	exe_path = create_exepath(input);
	cmd = malloc(sizeof(t_cmd));
	cmd->exe_path = exe_path;
	cmd->name = ft_strrchr(exe_path, '/') + 1;
	return (cmd);
}