#include "main_include.h"
#include "parse_main.h"
#include "table.h"

//todo: enum적용하는 법... 
#define CMD 1
#define redirct 3

int		get_tkntype_zero(char *input)
{

	if (*input == '<' || *input == '>')
		return (redirct);
	//todo: 그 외 다른 pdf요구사항..is_cmd가 제일 마지막으로
	else if (ft_isalpha(*input) > 0)
		return (is_cmd());
	else
		return (none);
}



void	*create_tbl(int tkn_type, char *input)
{
	if (tkn_type == cmd)
		return (set_cmd(input));
	else if (tkn_type == redirct)
		return (set_rediret(input));
}

t_lex	*create_lex(int tkn_type, char *input)
{
	t_lex	*lex;
	
	if (tkn_type < 0)
		return (NULL);
	lex = malloc(sizeof(t_lex));
	lex->tkn_type = tkn_type;
	lex->tbl = create_tbl(lex->tkn_type, input);
}

char	*quote_state_zero(char *input)
{
	int		tkn_type;
	t_lex	*lex;
	t_node	*node;

	tkn_type = -1;
	tkn_type = get_tkntype_zero(input);
	lex = create_lex(tkn_type, input);
}

