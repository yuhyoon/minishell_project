#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "libft/libft.h"
#include "builtin.h"
#include "delete.h"
#include "errno.h"

extern unsigned char exitcode;

typedef struct s_minish
{
	char	*src;
	char	*mask;
	t_list	*ready;
	pid_t	*child_pids;
	int		cmd_num;
	int		prev_for_pipe;
	//pid_t	pid;
	char	**envp;
	struct s_envp	*n_envs;
	struct s_envp	*n_export;
	char	*pwd;
}t_minish;

void	set_signal(void *handler);
void	before_readline(int signal);

void    f_init_envps(t_minish *sh);

//builtins
int f_cd(t_minish *sh);
int f_echo(t_minish *sh);
int f_pwd(t_minish *sh);
int f_exit(t_minish *sh);

#endif
