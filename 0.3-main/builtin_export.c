/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:49:16 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/18 07:17:41 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// export 정렬
void bubble_sort_envp(char **envp, int count)
{
    int i;
    int j;
    char *temp;

    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - i - 1)
        {
            if (ft_strncmp(envp[j], envp[j + 1], ft_strlen(envp[j])) > 0)
            {
                temp = envp[j];
                envp[j] = envp[j + 1];
                envp[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

// export node 생성
void f_sort_and_store_envp(char **envp, t_envp **sorted_envp)
{
    int count;
    int i;
    char **sorted_envp_array;

    count = f_count_char(envp);
    i = -1;
    sorted_envp_array = NULL;
    if (!envp || !sorted_envp)
    {
        ft_putstr_fd("Invalid Inputs", 2); // 지우기
        return;
    }
    sorted_envp_array = (char **)malloc(sizeof(char *) * (count + 1));
    if (!sorted_envp_array)
    {
        ft_putstr_fd("Failed allocated", 2); // 지우기
        return;
    }
    while (++i < count)
        sorted_envp_array[i] = ft_strdup(envp[i]);
    sorted_envp_array[i] = NULL;
    bubble_sort_envp(sorted_envp_array, count);
    f_init_env(sorted_envp_array, sorted_envp);
    free_double_char(sorted_envp_array);
}

// void	print_export(t_envp *list)
// {
//     t_envp  *tmp;
//     int i = 0;

//     tmp = list;
// 	while (tmp)
// 	{
//         write(1, "declare -x ", 11);
// 		write(1, tmp->key ,ft_strlen(tmp->key));
// 		if (tmp->value)
//         {
//             write(1, "=\"", 2);
// 			write(1, tmp->value, ft_strlen(tmp->value));
//             write(1, "\"", 2);
//         }
// 		write(1, "\n", 1);
// 		tmp = tmp->next;
//         i++;
// 	}
// }

// 확인용 (minishell 함수 아님) //평가 받기 전 삭제 필수
//  void	show_stack(t_envp *stack, char *str)
//  {
//  	int i = 0;
//  	printf(" SHOWSTACK [%s]\n", str);
//  	while (stack && stack != NULL)
//  	{
//  		printf("%d %s [%s]\n", i, stack->key, stack->value);
//  		stack = stack->next;
//  		i++;
//  	}
//  	printf("%s\n", "NULL");
//  }

void print_export(t_envp *lst)
{
    // t_envp *tmp;

    // tmp = *list; // 원본 리스트 복사
    while (lst)
    {
        ft_putstr_fd("declare -x ", 2);
        // (1, , 11);
        ft_putstr_fd(lst->key, 2);
        // write(1, lst->key, ft_strlen(lst->key));
        if (lst->value)
        {
            ft_putstr_fd("=\"", 2);
            ft_putstr_fd(lst->value, 2);
            ft_putstr_fd("\"", 2);
            // write(1, "", 2);
            // write(1, lst->value, ft_strlen(lst->value));
            // write(1, "\"", 1);
        }
        ft_putstr_fd("\n", 2);
        lst = lst->next;
    }
}

// //free_minish 입력 시 void로 변경
// int f_exit(t_minish *sh)
// {
//     char    **cmds;
//     t_list  *commands;
//     int     size;

//     cmds = ((t_ready *)(sh->ready->content))->cmd;
//     commands = (((t_ready *)(sh->ready->content))->text);
//     size = ft_lstsize(commands);
//     if (size == 1)
//         f_exit_only(0);
//     else if (size > 2)
//         f_exit_with_msg(size, cmds[1]);
//     // return (0); //free_minish
// }

void export_err_msg(char **cmds)
{
    int i;

    i = 2;
    while (cmds[i] != NULL)
    {
        ft_putstr_fd("minishell: export: ", 2);
        if (cmds[i])
        {
            ft_putstr_fd("`", 2);
            ft_putstr_fd(cmds[i], 2);
            ft_putstr_fd("': ", 2);
        }
        ft_putstr_fd("not a valid identifier\n", 2);
        i++;
    }
}

// void debug_list(t_envp *list)
// {
//     t_envp *tmp = list;
//     while (tmp)
//     {
//         printf("Node key: %s, value: %s\n", tmp->key, tmp->value);
//         tmp = tmp->next;
//     }
// }

int f_export(t_minish *sh)
{
    char **cmds;
    int size;

    cmds = ((t_ready *)sh->ready->content)->cmd;
    size = f_count_char(cmds);
    if (size == 1)
        print_export(sh->n_export);
    else if (size > 1) // 2개 이상
    {
        update_or_add_envp_node(&(sh->n_export), cmds[1]);
        if (size > 2)
            export_err_msg(cmds);
    }
    // debug_list(sh->n_export);
    exitcode = 0;
    return (0); // 정상 종료
}