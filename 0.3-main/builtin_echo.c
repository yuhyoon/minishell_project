/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:47:10 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/13 13:51:29 by hyeyeom          ###   ########.fr       */
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
