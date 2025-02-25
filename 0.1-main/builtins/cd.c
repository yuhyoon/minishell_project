/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 02:12:09 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/02/25 13:22:07 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include "../parse_main.h"

void	f_putstr_fd_error_msg(char *builtin, char *msg, char *location, int fd)
{
	ft_putstr_fd("bash: ", fd); 
	ft_putchar_fd(builtin, fd);
	ft_putstr_fd(": ", fd); 
	ft_putstr_fd(location, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

int f_cd_root()
{
    if (chdir("/") == -1)
    {
        ft_putchar_fd("bash: cd", 2);
		exitcode = 1;
        return (1);
    }
	exitcode = 0;
    return (0);
}

//cd ~ (home) 
int	f_cd_home(t_minish *sh)
{
	char	*home;

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
	return (0);
}

char *f_getenv(char **custom_envp, const char *name)
{
    size_t	name_len;
    int i;
	
	i = 0;
    if (!name || !custom_envp || ft_strlen(name) == 0)
        return (NULL);

    name_len = ft_strlen(name);
    while (custom_envp[i])
    {
        if (strncmp(custom_envp[i], name, name_len) == 0 && \
			custom_envp[i][name_len] == '=')
            return (&custom_envp[i][name_len + 1]);
        i++;
    }
    return (NULL);
}

//cd - (oldpwd 확인)
int	f_cd_go_back(t_minish *sh) 
{
	char	*oldpwd;

	oldpwd = f_getenv(sh->envp, "OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		exitcode = 1;
		return (1);
	}
	if (chdir(oldpwd) == -1)
	{
		f_putstr_fd_error_msg("cd", "No such file or directory", oldpwd, 2);
		exitcode = 1;
		return (1);
	}
	ft_putstr_fd(oldpwd, 1);
	ft_putchar_fd('\n', 1);
	exitcode = 0;
	return (0);
}


int	f_update_pwds(t_minish *sh, char *updated)
{
	char *tmp;
	char *tmp_oldpwd;
	
	tmp = sh->pwd;
	tmp_oldpwd = tmp;
	sh->pwd = getcwd(NULL, 0);

	if (!sh->pwd)
	{
		ft_putstr_fd("bash: cd: Error updating PWD\n", 2);
		exitcode = 1;
		return (1);
	}
	if (f_update_env(sh, "PWD", sh->pwd) == -1 || f_update_env(sh, "OLDPWD", tmp_oldpwd) == -1)
	{
		ft_putstr_fd("bash: cd: Error updating environment variables\n", 2);
		exitcode = 1;
		return (1);
	}
	exitcode = 0;
	return (0);
}

//
int	f_cd_goto(char *location)
{
	int	res;

	res = 0;
	if (access(location, F_OK) == -1)
	{
		f_putstr_fd_error_msg("cd", "Permission denied", location, 2);
		exitcode = 1;
		return (1);
	}
	if (ft_strncmp(location[0], "\\", 1) != 0)
		res = chdir(location);
	if (res == -1 || (ft_strncmp(location[0], "\\", 1) == 0))
	{
		f_putstr_fd_error_msg("cd", "No such file or directory", location, 2);
		exitcode = 1;
		return (1);
	}
	exitcode = 0;
	return (0);
}

int	f_check_params(char *param1, int length)
{
	int res;

	res = 3;
	if (ft_strncmp(param1, "-", ft_strlen(param1)) == 0)
		res = 1;
	else if (ft_strncmp(param1, "~", ft_strlen(param1)) == 0)
		res = 2;
	else if (ft_strncmp(param1, "/", ft_strlen(param1)) == 0)
		res = 3;
	else
		res = 4;
	return (res);
}

int f_cd(t_minish *sh)
{
	int     size;
	int		res;
	t_list 	*commands;
	t_list  *rdy_list;

	commands = (((t_ready *)(sh->ready->content))->text);
	size = ft_lstsize(commands);
	if (size == 1) //cd home
		f_cd_home(sh);
	else if (size > 1) // 2개 이상 들어와도 cd 바로 뒷 param만 확인해서 있는 경론지 확인 (나머지는 다 무시)
	{
		res = f_check_params((char *)commands->next->content, ft_strlen((char *)commands->next->content));
		if (res == 1)
			res = f_cd_go_back(sh);
		else if (res == 2)
			res = f_cd_home(sh);
		else if (res == 3)
			res = f_cd_root(); //시스템 상에서 없을 수 도 있나?
		else if (res = 4)
			res = f_cd_goto((char *)commands->next->content);
	}
	if (res == 0)
		f_update_pwds(sh, (char *)commands->next->content);
	exitcode = res;
	return (res);
}

// int main(int argc, char const *argv[])
// {
// 	t_minish sh = { .src = NULL, .mask = NULL, .ready = NULL, .pid = 0, .old_pipe = NULL, .new_pipe = NULL, .envp = NULL, .n_envs = NULL, .n_export = NULL, .pwd = NULL };

// 	t_ready ready1 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };
// 	t_ready ready2 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };
// 	t_ready ready3 = { .text = NULL, .rdrct = NULL, .in = NULL, .out = NULL };

// 	t_list *text1_node1 = ft_lstnew("ls");
// 	t_list *text1_node2 = ft_lstnew("-l");
// 	text1_node1->next = text1_node2;

// 	t_list *text2_node1 = ft_lstnew("grep");
// 	t_list *text2_node2 = ft_lstnew("main");
// 	text2_node1->next = text2_node2;

// 	t_list *text3_node1 = ft_lstnew("env");

// 	ready1.text = text1_node1;
// 	ready2.text = text2_node1;
// 	ready3.text = text3_node1;

// 	t_list node1 = { .content = &ready1, .next = NULL };
// 	t_list node2 = { .content = &ready2, .next = NULL };
// 	t_list node3 = { .content = &ready3, .next = NULL };

// 	node1.next = &node2;
// 	node2.next = &node3;

// 	sh.ready = &node1;

// 	execute_commands();
// 	return 0;
// }