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
#include "builtins/builtin.h"
#include "delete.h"
#include "errno.h"

extern unsigned char exitcode;
extern int	g_shmode;

// 각 자리수에 의미가 있음 (비트 연산할꺼면 생각 좀 해봐야겠음)
// 	1 0 
// 	10의 자리 수가 미니쉘 프로세스 단계 (실행 전에 확인하는 단계들을 거칠 때 사용)
// 	1의 자리수가 에러유무 
// 		0은 에러 없음 / 1 빌트인 명령어 에러 / bash 2가 에러  / 3 시그널 
// 	exit 

typedef enum	e_shmode
{
	PROMPT_OK = 10, 
}t_shmode;

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
	t_envp	*n_envs;
	t_envp	*n_export;
	char	*pwd;
	int		last_exit;
}t_minish;



void	set_signal(void *handler);
void	before_readline(int signal);

void    f_init_envps(t_minish *sh);

#endif
