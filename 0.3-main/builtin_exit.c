/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:05:44 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/17 14:55:22 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exit_err_msg(char *copy_str, int code)
{
    ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	if (copy_str)
    {
        ft_putstr_fd(copy_str, 2);
        ft_putstr_fd(": ", 2);
    }
    if (code == 1)
    	ft_putstr_fd("too many arguments\n", 2);
    else if (code == 2)
	    ft_putstr_fd("numeric argument required\n", 2);
    exit(code);
}

int check_exit_cmd(char *second_cmd)
{
    int     code;
    char    *tmp;

    code = 0;
    tmp = second_cmd;
    while (*tmp)
    {
        if (ft_isalnum(*tmp) != 4)
            break;
        (*tmp)++;
    }
    if (*tmp != '\0')
        code = -1;
    else
        code = ft_atoi(second_cmd);
    return (code);
}

void    f_exit_only(int exitcode)
{
    ft_putstr_fd("exit\n", 2);
    exit(255 & exitcode);
}

void    f_exit_with_msg(int size, char *second_cmd)
{
    int code;
   
    code = check_exit_cmd(second_cmd);
    if (size == 2)
    {
        if (code > 0)
            f_exit_only(code);
        else if (code == -1)
            exit_err_msg(second_cmd, 2);
    }
    else if (size > 2)
    {
    //  second_cmd 가 유효하지 않은데 (e.g. 214748364a7) too many 면 numeric 우선
    //  second_cmd 가 유효한데 (e.g. 2147483647) too many 면 too many
        if (code == -1)
            exit_err_msg(second_cmd, 2);
        else
            exit_err_msg(NULL, 1);
    }
}

//free_minish 입력 시 void로 변경
int f_exit(t_minish *sh)
{
    // t_list  *commands;
    // commands = (((t_ready *)(sh->ready->content))->text);
    char    **cmds;
    int     size;
    
    cmds = ((t_ready *)sh->ready->content)->cmd;
    size = f_count_char(cmds);
    if (size == 1)
        f_exit_only(0);
    else if (size > 2)
        f_exit_with_msg(size, cmds[1]);
    // return (0); //free_minish
}