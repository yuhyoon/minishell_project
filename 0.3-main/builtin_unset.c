/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:10:39 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/18 12:46:00 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	f_unset(t_minish *sh)
{
	char    **cmds;
    int     size;
	int		i;
    
    cmds = ((t_ready *)sh->ready->content)->cmd;
    size = f_count_char(cmds);
	if (size > 1)
	{
		i = 0;
		while (++i < size)
		{
			delete_t_envp(&(sh->n_export), cmds[i]);
			delete_t_envp(&(sh->n_envs), cmds[i]);
			// delete_double_char(sh->envp, cmds[i]);
		}
	}
	return (0);
}