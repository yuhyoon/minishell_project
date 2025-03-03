/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:27:35 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/02/24 01:49:03 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

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

//이게 맞는건지.. 아니면 node비교로? 고민되는구만
void bubble_sort_envp(char **envp, int count)
{
    int i; 
	int j; 
    char *temp;
	i = -1;
    while (++i < (count - 1))
    {
		j = 0;
        while (++j < count)
        {
            if (ft_strcmp(envp[j], envp[j + 1]) > 0)
            {
                temp = envp[j];
                envp[j] = envp[j + 1];
                envp[j + 1] = temp;
            }
        }
    }
}

//왝.. 너무 길다 프리하는 부분 기존걸로 쓰기(확인 해야함)
void f_sort_and_store_envp(char **envp, t_envp **sorted_envp)
{
    int count;
    int i;
    char **sorted_envp_array;
	
    if (!envp || !sorted_envp)
        return;
    count = 0;
    while (envp[count])
        count++;
    sorted_envp_array = (char **)malloc(sizeof(char *) * (count + 1));
    if (!sorted_envp_array)
        return;
    i = 0;
    while (i < count)
    {
        sorted_envp_array[i] = ft_strdup(envp[i]);
        i++;
    }
    sorted_envp_array[i] = NULL;
    bubble_sort_envp(sorted_envp_array, count);
    f_init_env(sorted_envp_array, sorted_envp);
    for (i = 0; i < count; i++)
        free(sorted_envp_array[i]);
    free(sorted_envp_array);
}

// //export 출력함수
// void	f_print_export()
// {

// }

//확인용 (minishell 함수 아님)
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
	t_envp *current;
	t_envp *next;

	current = *envp;
	while (current)
	{
		next = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*envp = NULL;
}

void	add_envp_node(t_envp **head, char *key, char *value)
{
	t_envp *new_node;
	t_envp *current;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->o_envp = NULL;
	new_node->count = 0;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}


int	update_envp_node(t_envp **head, char *key, char *value)
{
	t_envp *current;

	current = *head;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
	}
	return (1);
	// add_envp_node(head, key, value);
}


void	update_or_add_envp_node(t_envp **head, char *key, char *value)
{
	if (update_envp_node(head, key, value) == 1)
		add_envp_node(head, key, value);
}

 
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_envp	**n_envps;
	t_envp *sorted_envps = NULL;

    // 정렬 후 리스트 생성
	
	
	
    f_sort_and_store_envp(envp, &sorted_envps);
    f_init_env(envp, n_envps); //노드가 생성된지 확인
    show_stack(*n_envps, "------------env------------\n");
	update_or_add_envp_node(n_envps, "NEW_VALUE", "Hello Worldz_");
	show_stack(*n_envps, "------------ADD------------\n\n");
	delete_envp_node(n_envps, "NEW_VALUE");
	show_stack(*n_envps, "------------DELETE------------\n\n");
	free_n_envps(n_envps);

	// char *chars = "";
	// execve("/bin/env", &chars, envp);

	return 0;
}
