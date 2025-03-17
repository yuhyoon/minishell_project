/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 02:12:09 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/17 07:19:39 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//header는 합칠때 다시 만지기...
#include "builtin.h"

char *f_getenv(char **custom_envp,  char *name);

//env 노드를 기준으로 malloc을 다시 해주는 것이 안전할 듯 
// pwd가 없을 때 삭제 해야하는데 이걸 기준으로 해주기 보다 node 업데이트 하고 그걸 기준으로 업데이트 하는 방향으로 수정하기
int update_sh_pwd(t_minish *sh, char *newpwd)
{ 
    int i;
    int flag;
    int test;

    i = -1;
    flag = 0;
    while ((++i > -1) && (sh->envp[i]))
    {
        if (ft_strncmp(sh->envp[i], "PWD=", 4) == 0)
        {
            flag = 1;
            free(sh->envp[i]);
            sh->envp[i] = ft_strjoin("PWD=", newpwd);
            if (sh->envp[i] == NULL)
                return (-1);
            break;
        }
    }
    //동적할당변수라 이렇게 하면 위험
    // if (!flag && (sh->envp[i] == NULL))
    //     sh->envp[i] = ft_strjoin("PWD=", newpwd);
    return (0);
}


int update_envps(t_minish *sh, char *newpwd, char *oldpwd)
{
    int res;
    int i;

    res = 0;
    if (update_envp_node(sh->n_envs, "PWD", newpwd) != 0)
        add_envp_node(sh->n_envs, "PWD", newpwd);
    if (update_envp_node(sh->n_envs, "OLDPWD", oldpwd) != 0)
        add_envp_node(sh->n_envs, "OLDPWD", oldpwd);
    if (update_envp_node(sh->n_export, "PWD", newpwd) != 0)
        add_envp_node(sh->n_export, "PWD", newpwd);
    if (update_envp_node(sh->n_export, "OLDPWD", oldpwd) != 0)
        add_envp_node(sh->n_export, "OLDPWD", oldpwd);
    sh->pwd = newpwd;
    res = update_sh_pwd(sh, newpwd);
    if (res == -1)
    {
        exitcode = 1;
        return (1); //envp 업데이트 실패
    }
    return (0);
}

int f_update_pwds(t_minish *sh, char *current_pwd)
{
    char *oldpwd;
    char *newpwd;

	exitcode = 1;
    oldpwd = ft_strdup(current_pwd);
    if (!oldpwd)
        return (1);
    newpwd = getcwd(NULL, 0);
    if (!newpwd)
    {
        free(oldpwd);
        return (1);
    }
    sh->pwd = newpwd;
    if (update_envps(sh, newpwd, oldpwd))
    {
        free(oldpwd);
        free(newpwd);
        return (1);
    }
    free(oldpwd);
    exitcode = 0;
    return (0);
}

// ft_putstr_fd_error_msg 수정
void f_putstr_fd_error_msg( char *builtin,  char *msg,  char *location, int fd)
{
    ft_putstr_fd("bash: ", fd);
    ft_putstr_fd(builtin, fd);
    ft_putstr_fd(": ", fd);
    ft_putstr_fd(location, fd);
    ft_putstr_fd(": ", fd);
    ft_putstr_fd(msg, fd);
    ft_putstr_fd("\n", fd);
}

// f_cd_root 수정
int f_cd_root()
{
    if (chdir("/") == -1)
    {
        ft_putstr_fd("bash: cd: Failed to change to root directory\n", 2);
        exitcode = 1;
        return (1);
    }
    exitcode = 0;
    return (0);
}

// f_cd_goto 수정
int f_cd_goto(char *location)
{
    int res;

    res = 0;
    if (access(location, F_OK) == -1)
    {
        f_putstr_fd_error_msg("cd", "Permission denied", location, 2);
        exitcode = 1;
        return (1);
    }
    if (location[0] != '\\')
        res = chdir(location);
    else
    {
        f_putstr_fd_error_msg("cd", "No such file or directory", location, 2);
        exitcode = 1;
        return (1);
    }
    exitcode = 0;
    return (0);
}
// f_cd_home 수정
int f_cd_home(t_minish *sh)
{
    char *home;

    home = f_getenv(sh->envp, "HOME");
    if (!home)
    {
        ft_putstr_fd("bash: cd: HOME not set\n", 2);
        exitcode = 1;
        return (1);
    }
    if (chdir(home) == -1)
    {
        ft_putstr_fd("bash: cd: Failed to change directory to HOME\n", 2);
        exitcode = 1;
        return (1);
    }
    // printf("home %s\n", home);
    exitcode = 0;
    return (0);
}

int f_cd_go_back(t_minish *sh)
{
    char *back;

    back = f_getenv(sh->envp, "OLDPWD");
    if (!back)
    {
        ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
        exitcode = 1;
        return (1);
    }
    if (chdir(back) == -1)
    {
        ft_putstr_fd("bash: cd: Failed to change directory to OLDPWD\n", 2);
        exitcode = 1;
        return (1);
    }
    exitcode = 0;
    return (0);
}

// f_check_params 수정
int f_check_params(char *param1, int length)
{
    if (ft_strncmp(param1, "-", length) == 0)
        return (1);
    else if (ft_strncmp(param1, "~", length) == 0)
        return (2);
    else if (ft_strncmp(param1, "/", length) == 0)
        return (3);
    else
        return (4);
}

// f_cd 수정
int f_cd(t_minish *sh)
{
    int	size; 
	int	res;
    char    *current_pwd;
    t_list  *commands;

    res = 0;
    current_pwd = getcwd(NULL, 0);
    if (!current_pwd)
        return (1);
    commands = (((t_ready *)(sh->ready->content))->text);
    // printf("f_cd %s\n", (char *) commands->content);
    size = ft_lstsize(commands);
    // printf("f_cd %d\n", size);
    if (size == 1)
        res = f_cd_home(sh);
    if (size > 1)
    {
        res = f_check_params((char *)commands->next->content, ((int)ft_strlen((char *)commands->next->content)));
        if (res == 1)
            res = f_cd_go_back(sh);
        else if (res == 2)
            res = f_cd_home(sh);
        else if (res == 3)
            res = f_cd_root();
        else if (res == 4)
            res = f_cd_goto((char *)commands->next->content);
        else //아직까진 괜찮음 이건 합치고도 다시 확인 
            printf("Unexpected condition\n");
    }
    // if (res == 0)
    //     f_update_pwds(sh, current_pwd);
    free(current_pwd); //free 여기서 해도 괜찮?
    return (res);
}


// //header는 합칠때 다시 만지기...
// #include "builtin.h"

// // unsigned char exitcode = 0;

// char *f_getenv(char **custom_envp,  char *name);

// //env 노드를 기준으로 malloc을 다시 해주는 것이 안전할 듯 
// // pwd가 없을 때 삭제 해야하는데 이걸 기준으로 해주기 보다 node 업데이트 하고 그걸 기준으로 업데이트 하는 방향으로 수정하기
// int update_sh_pwd(t_minish *sh, char *newpwd)
// { 
//     int i;
//     int flag;
//     int test;

//     i = -1;
//     flag = 0;
//     while ((++i > -1) && (sh->envp[i]))
//     {
//         if (ft_strncmp(sh->envp[i], "PWD=", 4) == 0)
//         {
//             flag = 1;
//             free(sh->envp[i]);
//             sh->envp[i] = ft_strjoin("PWD=", newpwd);
//             if (sh->envp[i] == NULL)
//                 return (-1);
//             break;
//         }
//     }
//     //동적할당변수라 이렇게 하면 위험
//     // if (!flag && (sh->envp[i] == NULL))
//     //     sh->envp[i] = ft_strjoin("PWD=", newpwd);
//     return (0);
// }


// int update_envps(t_minish *sh, char *newpwd, char *oldpwd)
// {
//     int res;
//     int i;

//     res = 0;
//     if (update_envp_node(sh->n_envs, "PWD", newpwd) != 0)
//         add_envp_node(sh->n_envs, "PWD", newpwd);
//     if (update_envp_node(sh->n_envs, "OLDPWD", oldpwd) != 0)
//         add_envp_node(sh->n_envs, "OLDPWD", oldpwd);
//     if (update_envp_node(sh->n_export, "PWD", newpwd) != 0)
//         add_envp_node(sh->n_export, "PWD", newpwd);
//     if (update_envp_node(sh->n_export, "OLDPWD", oldpwd) != 0)
//         add_envp_node(sh->n_export, "OLDPWD", oldpwd);
//     sh->pwd = newpwd;
//     res = update_sh_pwd(sh, newpwd);
//     if (res == -1)
//     {
//         exitcode = 1;
//         return (1); //envp 업데이트 실패
//     }
//     return (0);
// }

// int f_update_pwds(t_minish *sh, char *current_pwd)
// {
//     char *oldpwd;
//     char *newpwd;

// 	exitcode = 1;
//     oldpwd = ft_strdup(current_pwd);
//     if (!oldpwd)
//         return (1);
//     newpwd = getcwd(NULL, 0);
//     if (!newpwd)
//     {
//         free(oldpwd);
//         return (1);
//     }
//     sh->pwd = newpwd;
//     if (update_envps(sh, newpwd, oldpwd))
//     {
//         free(oldpwd);
//         free(newpwd);
//         return (1);
//     }
//     free(oldpwd);
//     exitcode = 0;
//     return (0);
// }

// // ft_putstr_fd_error_msg 수정
// void f_putstr_fd_error_msg( char *builtin,  char *msg,  char *location, int fd)
// {
//     ft_putstr_fd("bash: ", fd);
//     ft_putstr_fd(builtin, fd);
//     ft_putstr_fd(": ", fd);
//     ft_putstr_fd(location, fd);
//     ft_putstr_fd(": ", fd);
//     ft_putstr_fd(msg, fd);
//     ft_putstr_fd("\n", fd);
// }

// // f_cd_root 수정
// int f_cd_root()
// {
//     if (chdir("/") == -1)
//     {
//         ft_putstr_fd("bash: cd: Failed to change to root directory\n", 2);
//         exitcode = 1;
//         return (1);
//     }
//     exitcode = 0;
//     return (0);
// }

// // f_cd_goto 수정
// int f_cd_goto(char *location)
// {
//     int res;

//     res = 0;
//     if (access(location, F_OK) == -1)
//     {
//         f_putstr_fd_error_msg("cd", "Permission denied", location, 2);
//         exitcode = 1;
//         return (1);
//     }
//     if (location[0] != '\\')
//         res = chdir(location);
//     else
//     {
//         f_putstr_fd_error_msg("cd", "No such file or directory", location, 2);
//         exitcode = 1;
//         return (1);
//     }
//     exitcode = 0;
//     return (0);
// }
// // f_cd_home 수정
// int f_cd_home(t_minish *sh)
// {
//     char *home;

//     home = f_getenv(sh->envp, "HOME");
//     if (!home)
//     {
//         ft_putstr_fd("bash: cd: HOME not set\n", 2);
//         exitcode = 1;
//         return (1);
//     }
//     if (chdir(home) == -1)
//     {
//         ft_putstr_fd("bash: cd: Failed to change directory to HOME\n", 2);
//         exitcode = 1;
//         return (1);
//     }
//     exitcode = 0;
//     return (0);
// }

// int f_cd_go_back(t_minish *sh)
// {
//     char *back;

//     back = f_getenv(sh->envp, "OLDPWD");
//     if (!back)
//     {
//         ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
//         exitcode = 1;
//         return (1);
//     }
//     if (chdir(back) == -1)
//     {
//         ft_putstr_fd("bash: cd: Failed to change directory to OLDPWD\n", 2);
//         exitcode = 1;
//         return (1);
//     }
//     exitcode = 0;
//     return (0);
// }

// // f_check_params 수정
// int f_check_params(char *param1, int length)
// {
//     if (ft_strncmp(param1, "-", length) == 0)
//         return (1);
//     else if (ft_strncmp(param1, "~", length) == 0)
//         return (2);
//     else if (ft_strncmp(param1, "/", length) == 0)
//         return (3);
//     else
//         return (4);
// }

// // f_cd 수정
// int f_cd(t_minish *sh)
// {
//     int	size; 
// 	int	res;
//     char    *current_pwd;
//     // t_list  *commands;
//     char    **commands;

//     res = 0;
//     current_pwd = getcwd(NULL, 0);
//     if (!current_pwd)
//         return (1);
//     commands = ((t_ready *)sh->ready->content)->cmd;
//     size = f_count_char(commands);
//     // printf("size : %d\n", size);
//     if (size == 1)
//         res = f_cd_home(sh);
//     else if (size > 1)
//     {
//         res = f_check_params(commands[1], ft_strlen(commands[1]));
//         // printf("res : %d\n ", res);
//         if (res == 1)
//             res = f_cd_go_back(sh); //cd home으로 이동 하도록 수정
//         else if (res == 2)
//             res = f_cd_home(sh);
//         else if (res == 3)
//             res = f_cd_root();
//         else if (res == 4)
//             res = f_cd_goto(commands[1]);
//         else //아직까진 괜찮음 이건 합치고도 다시 확인 
//             printf("Unexpected condition\n");
//     }
//     // if (res == 0) // 수정..
//     //     f_update_pwds(sh, current_pwd);
//     free(current_pwd); //free 여기서 해도 괜찮?
//     return (res);
// }

// //// t_ready 노드 하나씩 실행되도록 설계 아래 부분에선 text1_node1 내부에 있는게 실행됌 
// // int main(int argc, char *argv[], char **envp)
// // {
// //     t_minish sh;
// //     int i = 0;
// //     while (envp[i])
// //     {
// //         // printf("%s\n", envp[i]);
// //         i++;
// //         // envp++;
// //     }
// //     printf("%d\n", i);
// //     sh.envp = (char **)malloc(sizeof(char *) * (i + 1));
// //     i = 0;
// //     while(envp[i])
// //     {
// //         sh.envp[i] = ft_strdup(envp[i]);
// //         i++;
// //     }
// //     printf("last %d\n", i);
// //     envp[i] = NULL;
// //     // 초기화
// //     sh.n_envs = NULL;
// //     sh.n_export = NULL;
// //     f_init_env(envp, &(sh.n_envs));
// //     // show_stack(sh.n_envs, "------------env------------\n");
// //     printf("-----------%s\n", sh.n_envs->key);
// //     printf("----------jasfjlkasjflkjsaljfdlk%s-\n", *sh.envp);

// //     f_sort_and_store_envp(sh.envp, &(sh.n_export));
// //     printf("------?-----%s\n", sh.n_export->key);
// //     // show_stack(sh.n_export, "------------export------------\n");
// //     t_ready ready1 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };
// //     t_ready ready2 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };
// //     t_ready ready3 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };
// //     t_ready ready4 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };

// //     t_list *text1_node1 = ft_lstnew("cd");
// //     t_list *text1_node2 = ft_lstnew("./tesr");
// //     text1_node1->next = text1_node2;

// //     t_list *text2_node1 = ft_lstnew("echo");
// //     t_list *text2_node2 = ft_lstnew("-nnnnnn");
// // 	t_list *text2_node3 = ft_lstnew("hi");
// //     text2_node1->next = text2_node2;
// // 	text2_node2->next = text2_node3;

// //     t_list *text3_node1 = ft_lstnew("echo");

// //     t_list *text4_node1 = ft_lstnew("hello");

// //     ready1.text = text1_node1;
// //     ready2.text = text2_node1;
// //     ready3.text = text3_node1;
// //     ready4.text = text4_node1;

// //     t_list node1 = { .content = &ready1, .next = NULL };
// //     t_list node2 = { .content = &ready2, .next = NULL };
// //     t_list node3 = { .content = &ready3, .next = NULL };
// //     t_list node4 = { .content = &ready4, .next = NULL };

// //     node1.next = &node2;
// //     node2.next = &node3;
// //     node3.next = &node4;

// //     sh.ready = &node1;

// //     f_cd(&sh);
// //     return 0;
// // }
