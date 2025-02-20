#include "envp.h"

int	f_count_double_char(char **chars)
{
	int count;

	count = 0;
	while (chars[count])
		count++;
	return (count);
}

int	f_count_envps(t_envp **envps)
{
	t_envp	*tmp;
	int		count;

	tmp = *envps;
	count = 0;
	while (*envps)
	{
		count++;
		envps = envps->next;
	}
	return (count);
}


void    free_double_char(char **chars)
{
    int i;
    int len;
    
    i = 0;
    len = f_count_double_char(chars);
    while (i < len && chars[i] != NULL)
    {
        free(chars[i]);
        i++;
    }
    free(chars);
}

t_envp	*new_node(char **envp, int idx)
{
	t_envp	*first;
	char	**split_envp;

	first = (t_envp *)malloc(sizeof(t_envp));
	if (!first)
		return (NULL);
    split_envp = ft_split(envp[idx], '=');
    first->key = ft_strdup(split_envp[0]);
    if (split_envp[1] != NULL)
        first->value = ft_strdup(split_envp[1]);
    else
        first->value = ft_strdup('\0');
    first->next = NULL;
	free_double_char(split_envp);
	return (first);
}

void	f_init_env(char **envp, t_envp *n_envps)
{
	int		count;
	int		i;
	t_envp	*tmp;

	count = f_count_double_char(envp);
	printf("var count : %d\n", count);
	n_envps = new_node(envp, 0);
	tmp = n_envps;
	i = 0;
	while (++i < count)
	{
		tmp->next = new_node(envp, i);
        if (tmp->next == NULL)
            return ;
        tmp->o_envp = envp;
		tmp->count = count;
		tmp = tmp->next;
	}
	// tmp->next = NULL;
}


int f_set_env(t_envp **n_envps, char *key, char *value)
{
    int i;
    int count;
    int res;
    int value_length;
    t_envp *n_node;

    res = 1;
    count = f_count_node_envps(n_envps);
    value_length = ft_strlen(value);
    i = -1;
    while (++i < count)
    {
        //기존에 있는걸 바꾸기
        if (ft_strncmp(n_envps[i], key, value_length) == 0)
        {
            res = 0;
            n_envps[i]->key = ft_strdup(key);
            n_envps[i]->value = ft_strdup(value);
            break;
        }
    }
    //다 돌아봤는데도 없었을때 추가 
	//와 지저분하다 수정 필요
    if (i == count)
    {
        char **new_envp = (char **)malloc(sizeof(char *) * 3);
        new_envp[0] = ft_strdup(key);
        new_envp[1] = ft_strdup(value);
        new_envp[2] = NULL;
        n_node = new_node(new_envp, i);
        n_envps[i] = n_node;
        free_double_char(new_envp);
    }
    if (res != 0)
        res = 1;
    return (res);
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_envp	*n_envps;
	
	n_envps = NULL;
    f_init_env(envp, n_envps); //노드가 생성된지 확인  
    f_set_env(envp, "NEW_VALUE", "Hello World");
	// f_update_env();
	// f_unset_env(envp, "NEW_VALUE");
	return 0;
}
