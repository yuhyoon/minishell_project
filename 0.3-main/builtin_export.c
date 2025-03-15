/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:49:16 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/14 00:01:22 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//export 정렬
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

//export node 생성
void f_sort_and_store_envp(char **envp, t_envp **sorted_envp)
{
    int count;
    int i;
    char **sorted_envp_array;

    if (!envp || !sorted_envp) {
        printf("Error: invalid input.\n");
        return;
    }
    count = 0;
    while (envp[count])
        count++;
    sorted_envp_array = (char **)malloc(sizeof(char *) * (count + 1));
    if (!sorted_envp_array) {
        printf("Error: memory allocation failed.\n");
        return ;
    }
    for (i = 0; i < count; i++)
        sorted_envp_array[i] = ft_strdup(envp[i]);
    sorted_envp_array[i] = NULL;
    bubble_sort_envp(sorted_envp_array, count);
    f_init_env(sorted_envp_array, sorted_envp);
    if (!*sorted_envp) {
        printf("Error: sorted_envp initialization failed.\n");
    }
    for (i = 0; i < count; i++)
        free(sorted_envp_array[i]);
    free(sorted_envp_array);
}

// //export 출력함수
int print_export()
{
    return (0);
}


int f_export(t_minish *sh)
{
    char    **commands;
    
    commands = ((t_ready *)sh->ready->content)->cmd;
    printf("commands %s\n", commands[0]);
    if (commands[1])
        printf("commands %s\n", commands[1]);
    // int i = 0;
    // while (i < 1)
    // {
    //     i++;
    // }
    return (0); //정상 종료
}