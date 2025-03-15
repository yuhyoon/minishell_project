/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:10:39 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/14 18:13:59 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// void	delete_envp_node(t_envp **head, char *key)
// {
	
// }

int	f_unset(t_minish *sh)
{
	char	*key;
	char	**commands;
	
	commands = ((t_ready *)sh->ready->content)->cmd;
	key = commands[1];
	// delete_envp_node();
	delete_t_envp(sh->n_export, key);
	delete_t_envp(sh->n_envs, key);
	// delete_double_char(sh->envp, key);
	return (0);
}