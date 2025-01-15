#include "main_include.h"
#include "parse_main.h"
#include "table.h"

int quote_state(char *line)
{
	int quot_state;

	if (*line != '\'' && *line != '\"')
		quot_state = 0;
	else if (*line != '\'')
		quot_state = 1;
	else if (*line != '\"')
		quot_state = 2;
	
	while (*line)
	{
		if (quot_state == 0)
		{
			quot_state_zero();
		}
		if (quot_state == 1)
		{
			if (*line == '\'')
				quot_state == 0;
		}
		if (quot_state == 2)
		{
			if (*line == '\"')
				quot_state == 0;
		}
	}
	unclose_quot();
}