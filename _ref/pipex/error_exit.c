/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:29:19 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/07/15 15:43:34 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	error_exit_errno(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	error_argc(int argc)
{
	if (argc != 5)
		error_exit("usage: ./pipex file1 cmd1 cmd2 file2");
}

void	error_exit_cmd(char **cmd, char *f_p, t_fds *fds)
{
	close_free(fds);
	if (cmd == NULL && f_p == NULL)
		error_exit("command error: pipex can excute shell command only");
	free_splited(cmd);
	free(f_p);
	error_exit_errno("command error");
}
