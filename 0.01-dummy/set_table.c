#include "main_include.h"
#include "parse_main.h"
#include "table.h"

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

t_cmd	*set_cmd(char *input)
{
	is_valid_cmd(input);
}