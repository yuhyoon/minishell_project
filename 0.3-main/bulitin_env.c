/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:27:35 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/13 23:30:15 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// t_envp	*new_node(char **envp, int idx)
// {
// 	t_envp	*first;
// 	char	**split_envp;
//     int     count;

//     count = f_count_char(envp);
// 	first = (t_envp *)malloc(sizeof(t_envp));
// 	if (!first)
// 		return (NULL);
//     split_envp = ft_split(envp[idx], '=');
//     first->key = ft_strdup(split_envp[0]);
//     if (split_envp[1] == NULL || split_envp[1][0] == '\0')
//         first->value = ft_strdup("\0");
//     else
//         first->value = ft_strdup(split_envp[1]);
//     first->o_envp = envp;
//     first->count = count;
//     first->next = 0;
// 	free_double_char(split_envp);
// 	return (first);
// }





// void	f_init_env(char **envp, t_envp **n_envps)
// {
// 	// int		count;
// 	int		i;
// 	t_envp	*tmp;

// 	tmp = new_node(envp, 0);
// 	*n_envps = tmp;
// 	i = 0;
//     while (envp[++i])
// 	{
// 		tmp->next = new_node(envp, i);
// 		tmp = tmp->next;
// 	}
// 	tmp->next = NULL;
// }


// typedef struct s_envp
// {
// 	char	**o_envp; //원래 envp;
// 	int		count;
// 	char	*key;
// 	char	*value;
// 	struct s_envp	*next;
// }				t_envp;


void	print_env(t_envp *list)
{
	while (list)
	{
		write(1, list->key ,ft_strlen(list->key));
		write(1, "=", 1);
		if (list->value)
			write(1, list->value, ft_strlen(list->value));
		write(1, "\n", 1);
		list = list->next;
	}
}

// typedef struct s_minish
// {
// 	char	*src;
// 	char	*mask;
// 	t_list	*ready;
// 	pid_t	*child_pids;
// 	int		cmd_num;
// 	int		prev_for_pipe;
// 	//pid_t	pid;
// 	char	**envp;
// 	struct s_envp	*n_envs;
// 	struct s_envp	*n_export;
// 	char	*pwd;
// }t_minish;

int	f_env(t_minish *sh)
{
	print_env(sh->n_envs);
	return (0); //정상종료
}