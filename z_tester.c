#include <stdio.h>

int	vaild_quote_single_double(int quote_flag, char s, int *single_quote_open, int *double_quote_open)
{
	if (quote_flag == '\"')
	{
		if (s == '\'')
			(*single_quote_open)++;
		else if (s == '\"')
		{
			(*double_quote_open)++;
			if ((*double_quote_open) == 2)
				return (2);
		}
	}
	else if (quote_flag == '\'')
	{
		if (s == '\"')
			(*double_quote_open)++;
		else if (s == '\'')
		{
			(*single_quote_open)++;
			if ((*single_quote_open) == 2)
				return (1);
		}
	}
    return (0);
}

int	vaild_quote(char *s, int quote_flag)
{
	char *start;
 	int single_quote_open;
	int double_quote_open;
	int	i;

	single_quote_open = 0;
	double_quote_open = 0;
	i = 0;
	while (s[i] != '\0') 
	{
		if (vaild_quote_single_double(quote_flag, s[i], &single_quote_open, &double_quote_open) == 1
		|| vaild_quote_single_double(quote_flag, s[i], &single_quote_open, &double_quote_open) == 2)
			break;
		i++;
	}
	if ((single_quote_open % 2 != 0) || (double_quote_open % 2 != 0))
		return (0);
	return (1);
}


int main() {
    char *test_string1 = "\"This is 'a test' with quotes.\""; // 올바른 문자열
    char *test_string2 = "\"This is 'an unmatched test.\"";   // 불완전한 문자열

    if (vaild_quote(test_string1, 34)) {
        printf("test_string1: true\n");
    } else {
        printf("test_string1: false\n");
    }

    if (vaild_quote(test_string2, 34)) {
        printf("test_string2: true\n");
    } else {
        printf("test_string2: false\n");
    }

    return 0;
}