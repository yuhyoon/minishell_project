// char	**ft_split(char const *s, char c)
// int	ft_strncmp(const char *s1, const char *s2, size_t n)

#include "main.h"

int	free_node(t_envp **stack)
{
	t_envp	*head;
	t_envp	*tmp;

	head = *stack;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(stack);
	return (0);
}

int	free_double_char(char **double_char)
{
    int i;
    int length;

	i = -1;
	length = count_double_char(double_char);
	while (++i < length)
        free(double_char[i]);
    free(double_char); 
}

// t_envp	*new_node(char **envp, int idx)
t_envp	*new_node(char **envp, int idx)
{
	t_envp	*first;
	char	**split_envp;

	first = (t_envp *)malloc(sizeof(t_envp));
	if (!first)
		return (NULL);
    split_envp = ft_split(envp[idx], '=');
    first->key = ft_strdup(split_envp[0]);
    first->value = ft_strdup(split_envp[1]);
    first->next = 0;
	free_double_char(split_envp);
	return (first);
}


// int	free_stack(t_list **stack)
// {
// 	t_list	*head;
// 	t_list	*tmp;

// 	head = *stack;
// 	while (head)
// 	{
// 		tmp = head;
// 		head = head->next;
// 		free(tmp);
// 	}
// 	free(stack);
// 	return (0);
// }

// int	f_count_node_env(t_envp **envp)
// {
//     t_list	*head;
// 	t_list	*tmp;

// 	head = *stack;
// 	while (head)
// 	{
// 		tmp = head;
// 		head = head->next;
// 		free(tmp);
// 	}
// 	free(stack);
// 	return (;
// 	// int count;

// 	// count = 0;
// 	// while ()
// 	// 	count++;
// 	// return (count);
// }

int	f_count_char_env(char **envp)
{
	int count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

void	f_init_env(char **envp, t_envp **n_envps)
{
	int		count;
	int		i;
	t_envp	*tmp;

	count = f_envp_count(envp);
	printf("var count : %d\n", count);
	*n_envps = new_node(envp, 0);
	tmp = *n_envps;
	i = 0;
	while (++i < count)
	{
		tmp->next = new_node(envp, i);
		tmp->count = count;
		tmp = tmp->next;
	}
	tmp->next = NULL;
}

int f_count_node_envps(t_envp **n_envps)
{
    int count;
    t_envp	*head;
	t_envp	*tmp;

    count = 0;
	head = *n_envps;
	while (head)
	{
		tmp = head;
        count++;
		head = head->next;
	}
    return (count);
    // int count;
    // t_envp *p_n_envps;

    // count = 0;
    // p_n_envps = *n_envps;

    // while ()
    // {
    //     p_n_envps = p_n_envps->next;
    // }
    // return (count);
}

int f_node_to_dstr(char **c_new_envp, t_envp **n_envps)
{
    int i;
    int count;
    char *each;
    char *keyjoin;
    // char **c_new_envp;
    
    i = -1;
    count = f_count_env();
    while (++i < count)
    {
        keyjoin = ft_strjoin(n_envps[i]->key, "=");
        each = ft_strjoin(keyjoin, n_envps[i]->value);
        c_new_envp[i] = ft_strdup(each);
        free(each);
        free(keyjoin);
    }
    return (0);
    
}

//mode 0 : env mode 1: export
// env : $_ (When Bash invokes an external command, the variable ‘$_’ is set to the full pathname of the command and passed to that command in its environment.)
// export : $_ 없음
int f_print_env_variables(t_envp **n_envps, int mode)
{
    int     count;
    t_envp	*head;
	t_envp	*tmp;

	head = *n_envps;
	while (head)
	{
		tmp = head;
        if (mode == 1)
        {
            printf("%s", "declare -x ");
            printf("%s=", head->key);
            printf("\"%s\"\n", head->key);
        }
        else
        {
            printf("%s=", head->key);
            printf("%s\n", head->key);
        }
		head = head->next;
	}
    return (0);
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
    //다 돌아봤는데도 없었을때 추가 //와 지저분하다 수정 필요
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


void    *del(t_envp node)
{
    node.count = 0;
    free_double_char(node.path);
    free_double_char(node.o_envp);
    free(node.key);
    free(node.value);
    node.next = NULL;
}

void    f_delete_node(t_envp *node, void (*del)(t_envp*))
{
    del(node);
    free(node);
}

int f_unset_env(t_envp **n_envps, char *key)
{
    int i;
    int count;
    int res;
    t_envp *tmp;

    res = 1;
    count = f_count_node_envps(n_envps);
    i = -1;
    tmp = *n_envps;
    t_envp *prev_tmp = NULL;
    while (++i < count)
    {
        //널까지 보던가?
        tmp = n_envps[i];
        if (ft_strncmp(n_envps[i], key, ft_strlen(key)) == 0)
        {
            res = 0;
            //delete node //검증 필요
            prev_tmp = n_envps[i - 1];
            prev_tmp->next = tmp->next;
            f_delete_node(tmp, &del);
            break;
        }
    }
    if (res != 0) // 찾는 변수가 없었음!!
        res = 1;
    return (res);
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_envp	**n_envps;
	
	n_envps = NULL;
    f_init_env(envp, n_envps); //노드가 생성된지 확인  
    f_set_env(envp, "NEW_VALUE", "Hello World");
	f_unset_env(envp, "NEW_VALUE");
	return 0;
}
