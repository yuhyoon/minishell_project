/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:36:52 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/07/26 11:04:21 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char **envp)
{
	char	*env;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	env = envp[i];
	return (env);
}

char	*full_path(char *envp, char **cmd)
{
	char	**d_envp;
	int		i;
	char	*cmd_path;
	char	*full_path;

	if (cmd == NULL)
		return (NULL);
	d_envp = ft_split(envp, ':');
	i = 0;
	cmd_path = ft_strjoin("/", cmd[0]);
	while (d_envp[i] != NULL)
	{
		full_path = ft_strjoin(d_envp[i], cmd_path);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_splited(d_envp);
	free(cmd_path);
	cmd_path = NULL;
	return (full_path);
}

void	create_child(char *f_p, char **cmd, int *pp, int flg)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{	
		close(pp[0]);
		if (dup2(pp[1], STDOUT_FILENO) == -1)
			error_exit_errno("dup2 error");
		close(pp[1]);
		if (execve(f_p, cmd, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		close(pp[1]);
		if (flg > 0)
			dup2(pp[0], flg);
		else
			dup2(pp[0], STDIN_FILENO);
	}
}

t_fds	*init_fds(int argc, char **argv)
{
	t_fds	*fds;
	int		in_fd;
	int		out_fd;
	int		*pp;

	in_fd = open(argv[1], O_RDONLY);
	if (in_fd == -1)
		error_exit_errno("something error file1");
	out_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
		error_exit_errno("something error file2");
	pp = malloc(sizeof(int) * 2);
	if (pp == NULL)
		error_exit("malloc return NULL");
	fds = malloc(sizeof(t_fds));
	if (!fds)
		error_exit("malloc return NULL");
	fds->in_fd = in_fd;
	fds->out_fd = out_fd;
	fds->pp = pp;
	fds->flg = -1;
	return (fds);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_fds	*fds;
	char	*p_env;
	char	**cmd;
	char	*f_p;

	error_argc(argc);
	i = 1;
	fds = init_fds(argc, argv);
	p_env = ft_getenv(envp);
	create_pipe(fds);
	while (++i <= argc - 2)
	{
		cmd = pipex_split(argv[i]);
		f_p = full_path(p_env, cmd);
		if (f_p == NULL)
			error_exit_cmd(cmd, f_p, fds);
		if (i == argc - 2)
			dup(fds->out_fd);
		create_child(f_p, &cmd[0], fds->pp, fds->flg);
		free_cmd_fp(cmd, f_p);
	}
	while (wait(NULL) > 0)
		continue ;
	close_free(fds);
}
