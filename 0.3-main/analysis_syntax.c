#include "analysis.h"

int	valid_meta(int token, char *mask)
{
	int	max;
	int	i;
	int	rsult;

	i = 0;
	rsult = 0;
	if (token == IN_RD || token == OUT_RD)
		max = 3;
	else if (token == PIPE)
		max = 2;
	while (i < max && mask[i] == token)
		i++;
	if (i == max)
		rsult = 3;
	return (rsult);
}

int	syntax_analysis(char *mask)
{
	int	i;
	int	cnt;
	int	meta;
	int	err_flg;

	i = 0;
	cnt = 0;
	err_flg = 0;
	meta = 0;
	if (mask[i] > 1)
		meta = mask[i];
	if (meta > 0)
		err_flg = valid_meta(mask[i], &mask[i]);
	return (err_flg);
}