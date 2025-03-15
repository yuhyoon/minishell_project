/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:18:18 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/14 18:49:59 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


// int is_builtin(char *cmd_name, t_minish *sh)
// {
// 	// t_list	*lst;
// 	// t_ready	*rdy;

//     // lst = sh->ready;
//     // rdy = (t_ready *)(lst->content);
//     // printf("[is_bulitin] %s %ld\n", cmd_name,  ft_strlen(cmd_name));
//     if (ft_strncmp(cmd_name, "cd", ft_strlen(cmd_name)) == 0)
//         return (1);
//     else if (ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name)) == 0)
//         return (2);
//     else if (ft_strncmp(cmd_name, "pwd", ft_strlen(cmd_name)) == 0)
//         return (3);
// 	else if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name)) == 0)
//         return (4);
// 	else if (ft_strncmp(cmd_name, "env", ft_strlen(cmd_name)) == 0)
//         return (5);
//     else if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name)) == 0)
//         return (6);
//     else if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name)) == 0)
//         return (7);
//     // printf("res %d\n", res);
//     return (0);
// }

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


int    execute_bulitin(int bulitin_num, t_minish *sh)
{
    int res;
	char	*cmd;
	t_ready *rdy;
    t_list *lst;
	
    lst = sh->ready;
	rdy = (t_ready *)(lst->content);
	cmd = (char *)rdy->text->content;
    // printf("[execute_bulitin] %s\n", cmd);

    res = 0;
    // char*  commands = ((t_ready *)(sh->ready->content))->text;
    // printf("[execute_bulitin] %s\n", commands);

    if (bulitin_num == 1)
        res = f_cd(sh);            
    else if (bulitin_num == 2)
        res = f_echo(sh);            
    else if (bulitin_num == 3)
        res = f_pwd(sh);            
    else if (bulitin_num == 4)
        res = f_export(sh);            
    else if (bulitin_num == 5)
        res = f_env(sh);            
    else if (bulitin_num == 6)
        res = 0; //f_unset
    else if (bulitin_num == 7)
        res = f_exit(sh);
    return (res);
}

// int execute_builtin(t_ready *rdy, t_minish *sh, int flag)
// {
// 	if (flag == 1)
// 		rdy->cmd = create_str_2(&rdy->text);
//     // printf()
//     if (is_builtin(rdy->cmd[0], sh))  // is_builtin 1:빌트인 아님 / 0: 빌트인임
//     {
//         printf("%s\n", "[execute_builtin] NO Bulitin");
//         return (0);// 빌트인 아님
//     }
//     printf("%s\n", "[execute_builtin] YES Bulitin");
//     return (1); // 빌트인임
// }