#ifndef MAIN_H
# define MAIN_H

// # include "../lib/libft/libft.h"
# include "../../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> //Ctrl키 

//사용가능한가?
# include <errno.h>

// typedef	struct s_env_node
// {
// 	t_envp	node_env;
// 	t_envp	node_export;
// 	char	**envps;
// }				t_env_node;

//환경변수 관리용 구조체
typedef struct s_envp
{
	char	**o_envp; //원래 envp;
	int		count;
	// char	**path;
	char	*key;
	char	*value;
	struct s_envp	*next;
}				t_envp;




// 시그널 관리 구조체
typedef struct	s_signal
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_signal;



#endif

// typedef struct s_shell
// {tcsetattr**argv;
// 	char	**envp;


// } t_shell;


// typedef struct s_token
// {
// 	char		**splited_cmd;
// 	t_token		*next;

// } t_token;