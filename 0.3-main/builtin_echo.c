/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:47:10 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/08 01:51:02 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#define TRUE_ 1
#define FALSE_ 0

void f_print_echo(t_list *param_list, int option_on) // 0 newline, 1 no_newline
{
    t_list *tmp;

    tmp = param_list;
    if (option_on)
        tmp = tmp->next;
    while (tmp)
    {
        write(1, tmp->content, ft_strlen((char *)tmp->content));
        if (tmp->next)
            write(1, " ", 1);
        tmp = tmp->next;
    }
    if (!option_on)
        write(1, "\n", 1);
}

int f_check_n_option(char *is_option)
{
	int i;

    if (!is_option || is_option[0] != '-')
        return (0); // 옵션 아님
    i = 1;
    while (is_option[i] == 'n')
        i++;
    if (is_option[i] != '\0')
        return (0);
    return (1);
}

int f_echo(t_minish *sh)
{
    t_list *commands;
    int size;

    commands = (((t_ready *)(sh->ready->content))->text);
    size = ft_lstsize(commands);
    if (size == 1)
        write(1, "\n", 1);
    if (size > 1)
    {
        if (f_check_n_option(((char *)commands->next->content)) == 0)
			f_print_echo(commands->next, FALSE_); // newline
        else
			f_print_echo(commands->next, TRUE_); // without newline (-n option)
    }
    return (0);
}

// int main(int argc, char const *argv[])
// {
//     t_minish sh;

//     t_ready ready1 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };
//     t_ready ready2 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };
//     t_ready ready3 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };

//     t_list *text1_node1 = ft_lstnew("echo");
//     t_list *text1_node2 = ft_lstnew("hello");
//     text1_node1->next = text1_node2;

//     t_list *text2_node1 = ft_lstnew("echo");
//     t_list *text2_node2 = ft_lstnew("-nnnnnn");
// 	t_list *text2_node3 = ft_lstnew("hi");
//     text2_node1->next = text2_node2;
// 	text2_node2->next = text2_node3;

//     t_list *text3_node1 = ft_lstnew("echo");

//     ready1.text = text1_node1;
//     ready2.text = text2_node1;
//     ready3.text = text3_node1;

//     t_list node1 = { .content = &ready1, .next = NULL };
//     t_list node2 = { .content = &ready2, .next = NULL };
//     t_list node3 = { .content = &ready3, .next = NULL };

//     node1.next = &node2;
//     node2.next = &node3;

//     sh.ready = &node1;

//     f_echo(&sh);
//     return 0;
// }
