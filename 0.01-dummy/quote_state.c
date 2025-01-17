#include "main_include.h"
#include "parse_main.h"
#include "table.h"

//caution: quote_state purpose is linking nodes. create node feature is relevent to state functions
// todo: linking nodes
int quote_state(char *input)
{
	int quot_state;
	t_node	*node;

	if (*input != '\'' && *input != '\"')
		quot_state = 0;
	else if (*input != '\'')
		quot_state = 1;
	else if (*input != '\"')
		quot_state = 2;
	
	while (*input != '\n')
	{
		if (quot_state == 0)
		{
			node = quot_state_zero(input);
		}
		if (quot_state == 1)
		{
			node = quote_state_single(input);
		}
		if (quot_state == 2)
		{
			node = quote_state_double(input);
		}
		//todo: error handling - node
		input++;
	}
	unclose_quot();
}