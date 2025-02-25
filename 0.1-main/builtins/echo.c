/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:47:10 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/02/25 16:25:27 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_main.h"

#define TURE_ 1
#define FALSE_ 0

void	f_print_newline(t_list *param_list, int no_newline) //0 newline 1 no_newline
{
	t_list *tmp;

	tmp = param_list;
	if (!no_newline)
		tmp = tmp->next;
	while (tmp->next)
	{
		write(1,tmp->content, ft_strlen((char *)tmp->content));
		tmp = tmp->next;
	}
	if (!no_newline)
		write(1, "\n", 1);
}

int f_check_n_option(char *is_option)
{
	int i;
	int count;
	
	count = ft_strlen(is_option);
	if (is_option[0] != '-')
		return (1);
	i = 1;
	while (i < count)
	{
		if (is_option[i] == 'n')
			i++;
		else
			break;
	}
	if (i != count)
		return (1);
	return (0);
}

int f_echo(t_minish *sh)
{
	t_list 	*commands;
	int     size;

	commands = (((t_ready *)(sh->ready->content))->text);
	size = ft_lstsize(commands);
	if (size == 1)
		write(1, "\n", 1);
	if (size > 2)
	{
		if (f_check_n_option(((char *)commands->next->content)))
			f_print_echo(((char *)commands->next), TURE_); //without newline (-n option)
		else
			f_print_echo(((char *)commands->next), FALSE_); //newline
	}
	return (0);
}