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

extern int exitcode;

/*

typedef struct s_ready
{
	t_list	*text;
	t_list	*rdrct;
	int		rdrct_num;
	char		**cmd;
	t_redrct	*rdrct_in;
	t_redrct	*rdrct_out;
	int		input;
	int		output;
}t_ready;
#endif

*/
typedef struct s_minish
{
	char	*src; //free
	char	*mask; //free
	t_list	*ready; //free
	pid_t	*child_pids; //free
	int		cmd_count; 
	int		prev_for_pipe;
	//pid_t	pid;
	char	**envp; //-> free_t_envp하나 만들어서 free_minish에 넣기
	struct s_envp	*n_envs;
	struct s_envp	*n_export;
	int		built_code;
	char	*pwd;
}t_minish;

// signal
void	set_signal(void *handler);
void	before_readline(int signal);
void	do_sigint_heredoc(int signum);
void	set_signal_heredoc(void);
void	set_signal_fork(void);

// void    f_init_envps(t_minish *sh);

//builtins
int init_envp(t_minish *sh, char **envp);
int f_cd(t_minish *sh);
int f_echo(t_minish *sh);
int f_pwd(t_minish *sh);
int f_exit(t_minish *sh);
int	f_env(t_minish *sh);
int f_export(t_minish *sh);
int	f_unset(t_minish *sh);


#endif
