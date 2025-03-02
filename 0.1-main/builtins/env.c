/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:27:35 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/02/28 22:44:20 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../main.h"
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
// void	bubble_sort_envp(char **envp, int count)
// {
//     int i; 
// 	int j; 
//     char *temp;
// 	i = -1;
//     while (++i < (count - 1))
//     {
// 		j = 0;
//         while (++j < count)
//         {
//             if (ft_strncmp(envp[j], envp[j + 1], ft_strlen(envp[j])) > 0)
//             {
// 				printf("여기?");
// 				temp = envp[j];
//                 envp[j] = envp[j + 1];
//                 envp[j + 1] = temp;
//             }
//         }
//     }
// }

void bubble_sort_envp(char **envp, int count)
{
    int	i;
	int	j;
    char	*temp;

    i = 0;
    while (i < count - 1) {
        j = 0;
        while (j < count - i - 1) {
            if (ft_strncmp(envp[j], envp[j + 1], ft_strlen(envp[j])) > 0) {
                temp = envp[j];
                envp[j] = envp[j + 1];
                envp[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}


void f_sort_and_store_envp(char **envp, t_envp **sorted_envp)
{
    int count;
    int i;
    char **sorted_envp_array;

    if (!envp || !sorted_envp) {
        printf("Error: invalid input.\n");
        return;
    }

    // 환경 변수 개수 계산
    count = 0;
    while (envp[count])
        count++;

    // 정렬된 환경 변수 배열 생성
    sorted_envp_array = (char **)malloc(sizeof(char *) * (count + 1));
    if (!sorted_envp_array) {
        printf("Error: memory allocation failed.\n");
        return;
    }

    // 배열 복사
    for (i = 0; i < count; i++)
        sorted_envp_array[i] = ft_strdup(envp[i]);
    sorted_envp_array[i] = NULL;

    // 정렬 수행
    bubble_sort_envp(sorted_envp_array, count);

    // f_init_env 호출하여 t_envp 구조체 초기화
    f_init_env(sorted_envp_array, sorted_envp);
    if (!*sorted_envp) {
        printf("Error: sorted_envp initialization failed.\n");
    }

    // 동적 메모리 해제
    for (i = 0; i < count; i++)
        free(sorted_envp_array[i]);
    free(sorted_envp_array);
}


//왝.. 너무 길다 프리하는 부분 기존걸로 쓰기(확인 해야함)
// void	f_sort_and_store_envp(char **envp, t_envp **sorted_envp)
// {
//     int count;
//     int i;
//     char **sorted_envp_array;
	
// 	sorted_envp_array = NULL;
//     if (!envp || !sorted_envp)
// 	{
// 		printf("error?");
//         return;
// 	}
// 	printf("어디임?");
//     count = 0;
//     while (envp[count])
//         count++;
//     sorted_envp_array = (char **)malloc(sizeof(char *) * (count + 1));
//     if (!sorted_envp_array)
//         return;
	
// 		printf("어디임?222");

//     i = 0;
//     while (i < count)
//     {
//         sorted_envp_array[i] = ft_strdup(envp[i]);
//         i++;
//     }
//     sorted_envp_array[i] = NULL;
	
// 	printf("어디임?33333");

//     bubble_sort_envp(sorted_envp_array, count);
// 	printf(" rjqjwfoihwoiaefhoiwhaofihewoihf :\n");
// 	f_init_env(sorted_envp_array, sorted_envp);
// 	// printf("sadfksajflk%s\n", sorted_envp)
	
	
//     // for (i = 0; i < count; i++)
//     //     free(sorted_envp_array[i]);
//     // free(sorted_envp_array);
// }

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

int	add_envp_node(t_envp **head, char *key, char *value)
{
	t_envp *new_node;
	t_envp *current;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return (-1);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->o_envp = NULL;
	new_node->count = 0;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (-1);
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (0);
}


// int	f_update_env(t_minish *sh, char *key, char *value)
// {
	
// }

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
			if (!current->value)
				return (-1);
			return (0);
		}
		current = current->next;
	}
	return (1);
	// add_envp_node(head, key, value);
}


// void	update_or_add_envp_node(t_envp **head, char *key, char *value)
// {
// 	if (update_envp_node(head, key, value) == 1)
// 		add_envp_node(head, key, value);
// }

//main에서 2개만 받는다고 했을 때, 이게 맞지...
void	update_or_add_envp_node(t_envp **head, char *set)
{
	char	*key;
	char	*value;
	char	**sets;
	int	res;
	sets = ft_split(set, '=');
	key = ft_strdup(sets[0]);
	if (!sets[1])
		value = ft_strdup("\0");
	else
	{
		value = ft_strdup(sets[1]);
		if (!value)
			return ;
	}
	if (update_envp_node(head, key, value) == 1)
		add_envp_node(head, key, value);
	
	free(key);
	free(value);
	free(sets[0]);
	free(sets[1]);
	free(sets);
}


// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;

//     t_envp *n_envps_head = NULL;
//     t_envp **n_envps = &n_envps_head; // 포인터 초기화
//     t_envp *sorted_envps = NULL; // 초기화 추가

//     // 정렬 후 리스트 생성
//     f_sort_and_store_envp(envp, &sorted_envps);
//     if (!sorted_envps) {
//         fprintf(stderr, "Error: sorted_envps initialization failed.\n");
//         return (1);
//     }

//     // 환경 변수 리스트 초기화
//     f_init_env(envp, n_envps);
//     if (!*n_envps) {
//         fprintf(stderr, "Error: n_envps initialization failed.\n");
//         return (1);
//     }

//     // 스택 출력
//     show_stack(*n_envps, "------------env------------\n");

//     // 환경 변수 추가
//     update_or_add_envp_node(n_envps, "NEW_VALUE='HELLO worlds'");
//     show_stack(*n_envps, "------------ADD------------\n\n");

//     // 환경 변수 삭제
//     delete_envp_node(n_envps, "NEW_VALUE");
//     show_stack(*n_envps, "------------DELETE------------\n\n");

//     // 메모리 해제
//     free_n_envps(n_envps);

//     return 0;
// }


// // int main(int argc, char **argv, char **envp)
// // {
// // 	(void)argc;
// // 	(void)argv;
// // 	t_envp	**n_envps;
// // 	t_envp *sorted_envps = NULL;

// //     // 정렬 후 리스트 생성
	
	
	
// //     f_sort_and_store_envp(envp, &sorted_envps);
// //     f_init_env(envp, n_envps); //노드가 생성된지 확인
// //     show_stack(*n_envps, "------------env------------\n");
// // 	update_or_add_envp_node(n_envps, "NEW_VALUE='HELLO worlds'");
// // 	// update_or_add_envp_node(n_envps, "NEW_VALUE", "Hello Worldz_");
// // 	show_stack(*n_envps, "------------ADD------------\n\n");
// // 	delete_envp_node(n_envps, "NEW_VALUE");
// // 	show_stack(*n_envps, "------------DELETE------------\n\n");
// // 	free_n_envps(n_envps);

// // 	// char *chars = "";
// // 	// execve("/bin/env", &chars, envp);

// // 	return 0;
// // }
