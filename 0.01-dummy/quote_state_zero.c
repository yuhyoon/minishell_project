#include "main_include.h"
#include "parse_main.h"
#include "table.h"

// todo: enum적용하는 법...
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
		return (create_cmd(input));
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
	return (lex);
}

// HOLD ON: allocate memory is carefully. Becuase it going to increase time and space complexity 
// char *create_tknstr(int len, char *nul_term, char *start)
// {
// 	char *tkn_str;
// 	int flg;
// 	int i;

// 	flg = 0;
// 	if (*nul_term != '\0')
// 		flg = 1;
// 	tkn_str = malloc(sizeof(char) * (len + flg + 1));
// 	while (i < (len + flg + 1))
// 	{
// 		tkn_str[i] = start[i];
// 		i++;
// 	}
// 	tkn_str[i] = '\n';
// 	return (tkn_str);
// }

t_node *quote_state_zero(char *input)
{
	int		tkn_type;
	t_lex	*lex;
	t_node	*node;
	int		i;

	tkn_type = -1;
	tkn_type = get_tkntype_zero(input);
	lex = create_lex(tkn_type, input);
	i = 0;
	while (input[i] != '\n' || input[i] != '|' || input[i] != '\'' || input[i] != '\"')
	{
		if (input[i] == ' ')
			input[i] = '\0';
		i++;
	}
	lex->tkn_start = input;
	lex->len = i;
	// HOLD ON
	//lex->tkn_str = create_tknstr(i, &input[i], input);
	node = ft_lstnew(lex);
	return (node);
}
