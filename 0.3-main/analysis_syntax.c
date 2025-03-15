#include "analysis.h"

int	valid_meta(int token, char *mask)
{
	int	max;
	int	i;
	int	rsult;
	int	j;

	i = 0;
	rsult = 0;
	if (token == IN_RD || token == OUT_RD)
		max = 3;
	else if (token == PIPE)
	{
		max = 2;
		j = 1;
		while (mask[i + j] == 0 && mask[i + j] != '\n')
			j++;
	}
	while (i < max && mask[i] == token)
		i++;
	if (mask[j] == '\n')
		rsult = 2;
	else if (i == max)
		rsult = 1;
	return (rsult);
}

int	syntax_analysis(const char *m, int *len)
{
	int	i;
	char	*mask;
	int	meta;
	int	err_flg;

	mask = (char *)m;
	if (mask == NULL)
		return (1);
	i = 0;
	err_flg = 0;
	meta = 0;
	while (i < *len && err_flg == 0)
	{
		if (mask[i] > 1 && mask[i] != '\n')
			meta = mask[i];
		if (meta > 0)
		{
			err_flg = valid_meta(mask[i], &mask[i]);
			meta = 0;
		}
			i++;
	}
	return (err_flg);
}
