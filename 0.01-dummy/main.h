#ifndef MAIN_H
# define MAIN_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> //Ctrl키 

//사용가능한가?
# include <errno.h>

//환경변수 관리용 구조체
typedef struct s_envp
{
	// char	*head;
	char	*key;
	char	*value;
	t_envp	*next;
	
}				t_envp;


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