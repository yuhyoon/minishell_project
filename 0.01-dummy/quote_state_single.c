#include "main_include.h"
#include "parse_main.h"
#include "table.h"

char	*combine_path(char *nul_terminated, char *anothr_terminated)
{
	int		nul_n;
	int		another_n;
	char	*combn;
	int		flg;
	int		i;
	int		j;

	nul_n = ft_strlen(nul_terminated);
	another_n = ft_d_strlen(anothr_terminated, ' ');
	flg = 0;
	i = 0;
	j = 0;
	if (*anothr_terminated != '\\')
		flg = 1;
	combn = (char *)malloc(nul_n + another_n + flg);
	while (i < nul_n + another_n)
	{
		if (i < nul_n)
			combn[i] = nul_terminated[i];
		if (i == nul_n && flg == 1)
		{
			combn[i] = '\\';
			i++;
		}
		while(i > nul_n)
		{
			combn[i] = anothr_terminated[j];
			j++;
			i = i + j;
		}
		i++;
	}
}

char	*get_accesspath(char *input, char *path_env)
{
	int	n;

	if (*input == '\\')
		n = ft_d_strlen(input, ' ');
	else
		n = ft_d_strlen(input, ' ') + 1; //If not path and only name, It should make to '/cmd'
	

}

//전제: meta characters are filtered.
int is_valid_cmd(char *input)
{
	// int		n;
	// char	**words;

	// n = get_size(input, ft_strlen(input), ' ');
	// words = (char **)malloc(sizeof(char *) * (n + 1));
	// if (words == NULL)
	// 	return (-1);

	char	*path_env;
	char	*cmd_path;

	path_env = getenv("PATH");
	cmd_path = get_accesspath(input, path_env);
	
}


int ft_ismeta(char *input)
{
    if (*input == '<' || *input == '>' || \
    *input == '|' || *input == '$' || *input == '&')
        return (1);
    else
        return (0);
}

int		get_tkntype_single(char *input)
{
	t_token	type;

	if (ft_ismeta(input) > 0 && ft_isalpha(*input) > 0)
		return (is_valid_cmd(input));
	else
		return (0); //0 is none
}

char	*quote_state_single(char *input)
{
	int		tkn_type;
	t_lex	*lex;
	t_node	*node;

	tkn_type = -1;
	tkn_type = get_tkntype_single(input);
	lex = create_lex(tkn_type, input);
}