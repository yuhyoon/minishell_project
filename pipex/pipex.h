/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:27:09 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/07/26 10:51:30 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_fds
{
	int		in_fd;
	int		out_fd;
	int		*pp;
	int		flg;
}			t_fds;

char	*ft_getenv(char **envp);
char	*full_path(char *envp, char **cmd);
t_fds	*init_fds(int argc, char **argv);
void	create_child(char *f_p, char **cmd, int *pp, int flg);
void	error_exit(char *msg);
void	error_exit_errno(char *msg);
void	error_argc(int argc);
void	error_exit_cmd(char **cmd, char *f_p, t_fds *fds);
void	close_free(t_fds *fds);
void	free_splited(char **abs);
void	free_cmd_fp(char **cmd, char *f_p);
char	**pipex_splited(char *s_dup, int w, char **abs);
int		pipex_get_size(char *s, int len);
int		pipex_quote(char *str_dup);
char	**pipex_split(char *s);
void	create_pipe(t_fds *fds);

#endif
