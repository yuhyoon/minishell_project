
#include "../envp.h"

int	f_count_char(char **envp)
{
	int count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

void	free_double_char(char **double_char)
{
    int i;
    int length;

	i = -1;
	length = f_count_char(double_char);
	while ((++i < length) && double_char[i])
        free(double_char[i]);
    free(double_char); 
}


t_envp	*new_node(char **envp, int idx)
{
	t_envp	*first;
	char	**split_envp;
    int     count;

    count = f_count_char(envp);
	first = (t_envp *)malloc(sizeof(t_envp));
	if (!first)
		return (NULL);
    split_envp = ft_split(envp[idx], '=');
    first->key = ft_strdup(split_envp[0]);
    if (split_envp[1] == NULL || split_envp[1][0] == '\0')
        first->value = ft_strdup("\0");
    else
        first->value = ft_strdup(split_envp[1]);
    first->o_envp = envp;
    first->count = count;
    first->next = 0;
	free_double_char(split_envp);
	return (first);
}

void	f_init_env(char **envp, t_envp **n_envps)
{
	// int		count;
	int		i;
	t_envp	*tmp;

	tmp = new_node(envp, 0);
	*n_envps = tmp;
	i = 0;
    while (envp[++i])
	{
		tmp->next = new_node(envp, i);
		tmp = tmp->next;
	}
	tmp->next = NULL;
}


void	show_stack(t_envp *stack, char *str)
{
	int i = 0;
	printf(" SHOWSTACK [%s]\n", str);
	while (stack && stack != NULL)
	{
		printf("%d %s [%s]\n", i, stack->key, stack->value);
		stack = stack->next;
		i++;
	}
	printf("%s\n", "NULL");
}
void	free_n_envps(t_envp **envp)
{
	int i = 0;

	while (*envp)
	{
		free((*envp)->key);
		if ((*envp)->value)
			free((*envp)->value);
		*envp = (*envp)->next;
	}
	free(envp);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_envp	**n_envps;
	
	n_envps = (t_envp **)malloc(sizeof(t_envp *));
    f_init_env(envp, n_envps); //노드가 생성된지 확인
    show_stack(*n_envps, "env");
	free_n_envps(n_envps);
    // f_set_env(envp, "NEW_VALUE", "Hello World");
	// f_unset_env(envp, "NEW_VALUE");
	return 0;
}
