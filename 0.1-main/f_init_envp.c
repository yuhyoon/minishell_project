/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_init_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:22:15 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/02/24 01:52:05 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
// #include "./builtins/builtin.h"

// main에 맞춰서 진행
void    f_init_envps(t_minish *sh)
{
    t_envp **n_envps;
    t_envp *sorted_envps;

    n_envps = (t_envp **)malloc(sizeof(t_envp *));
    sorted_envps= NULL;
    f_init_env(sh->envp, sh->n_envs);
    f_sort_and_store_envp(sh->envp, sh->n_export); //이름 변경
}