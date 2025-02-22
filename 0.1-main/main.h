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
#include <dirent.h>
#include "libft/libft.h"

//study: multiple definition
//unsigned char	exitcode;

extern unsigned char exitcode;

typedef struct s_pipe
{
	int				pipe_fd[2];
	int				*read_fd;
	int				*write_fd;
}	t_pipe;

typedef struct s_minish
{
	char	*input;
	char	*mask;
	t_list	*ready;
	pid_t	pid;
	t_pipe	old_pipe;
	t_pipe	new_pipe;
	char	**envp;
	t_envp	*n_envs;
	t_envp	*n_export;
	char	*pwd;
}t_minish;

#endif
