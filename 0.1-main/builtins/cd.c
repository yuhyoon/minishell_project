/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 02:12:09 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/02/27 17:33:26 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include "../parse_main.h"

char *f_getenv(char **custom_envp,  char *name);

int update_sh_pwd(t_minish *sh, char *newpwd)
{ 
    int i;
    int flag;

    i = -1;
    flag = 0;
    while (!(sh->envp[i]) && (++i))
    {
        if (ft_strncmp(sh->envp[i], "PWD", ft_strlen(sh->envp[i])) == 0)
        {
            flag = 1;
            free(sh->envp[i]);
            sh->envp[i] = ft_strjoin("PWD=", newpwd);
            break;
        }
    }
    if (!flag && !(sh->envp))
        sh->envp[i] = ft_strjoin("PWD=", newpwd);
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
    update_sh_pwd(sh, newpwd);
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
        return 1;
    }
    exitcode = 0;
    return 0;
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
        return 1;
    }
    if (chdir(home) == -1)
    {
        ft_putstr_fd("bash: cd: Failed to change directory to HOME\n", 2);
        exitcode = 1;
        return 1;
    }
    exitcode = 0;
    return 0;
}

// f_getenv 수정 (이거 env.c 옮겨놓기)
char *f_getenv(char **custom_envp, char *name)
{
    size_t name_len;
    int i = 0;

    if (!name || !custom_envp || ft_strlen(name) == 0)
        return NULL;

    name_len = ft_strlen(name);
    while (custom_envp[i])
    {
        if (ft_strncmp(custom_envp[i], name, name_len) == 0 && custom_envp[i][name_len] == '=')
            return &custom_envp[i][name_len + 1];
        i++;
    }
    return NULL;
}

// f_cd_goto 수정
int f_cd_goto(char *location)
{
    int res;

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

// f_check_params 수정
int f_check_params(char *param1, int length)
{
    if (ft_strncmp(param1, "-", length) == 0)
        return 1;
    else if (ft_strncmp(param1, "~", length) == 0)
        return 2;
    else if (ft_strncmp(param1, "/", length) == 0)
        return 3;
    else
        return 4;
}

// f_cd 수정
int f_cd(t_minish *sh)
{
    int	size; 
	int	res;
    char    *current_pwd;
    t_list  *commands;

    current_pwd = getcwd(NULL, 0);
    if (!current_pwd)
        return (1);
    commands = (((t_ready *)(sh->ready->content))->text);
    size = ft_lstsize(commands);
    if (size == 1) // cd home
        return f_cd_home(sh);
    if (size > 1)
    {
        res = f_check_params((char *)commands->next->content, ft_strlen((char *)commands->next->content));
        if (res == 1)
            res = f_cd_go_back(sh);
        else if (res == 2)
            res = f_cd_home(sh);
        else if (res == 3)
            res = f_cd_root();
        else if (res == 4)
            res = f_cd_goto((char *)commands->next->content);
        else
            printf("Unexpected condition\n");
    }
    if (res == 0)
        f_update_pwds(sh, current_pwd);
    free(current_pwd); //free 여기서 해도 괜찮?
    return res;
}

// 실행 아직 안함
// int main(int argc, char *argv[])
// {
//     t_minish sh;

//     t_ready ready1 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };
//     t_ready ready2 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };
//     t_ready ready3 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };

//     t_list *text1_node1 = ft_lstnew("cd");
//     t_list *text1_node2 = ft_lstnew("./tesr");
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

//     f_cd(&sh);
//     return 0;
// }
