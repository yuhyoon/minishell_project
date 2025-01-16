#include "main_include.h"
#include "parse_main.h"
#include "table.h"

//전제: meta characters are filtered.
int create_exepath(char *input)
{
	char	**paths;
	int		i;
	char	*cmd_path;
	char	*exe_path;

	paths = ft_split(getenv("PATH"), ':');
	cmd_path = get_cmdpath(input);
	i = 0;
	while (paths[i] != NULL)
	{
		exe_path = ft_strjoin(paths[i], cmd_path);
		if (access(exe_path, X_OK) == 0)
			break ;
		free(exe_path);
		exe_path = NULL;
		i++;
	}
	//todo: double_free(paths);
	free(cmd_path);
	return (exe_path);
}

//todo1: implement - evaluate same sequnced character
//todo2: add - don't use meta character(e.g: ;)

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

	if (ft_ismeta(input) == 0 && ft_isalpha(*input) > 0)
		return (1); //1 is cmd
	else
		return (0); //0 is none
}

void	*quote_state_single(char *input)
{
	int		tkn_type;
	t_lex	*lex;

	tkn_type = -1;
	*input = '\0';
	input++;
	tkn_type = get_tkntype_single(input);
	lex = create_lex(tkn_type, input);
	if (lex == NULL)
		//todo: error or return NULL
	while (*input != '\'' || *input != '\0')
		input++;
	if (*input == '\'')
	{
		*input = '\0';
		return (lex);
	}	
	else
	{
		free_tbl(lex, tkn_type);
		error();
	}
}