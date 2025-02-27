#include "main.h"
#include "parse_main.h"
# include "token_step-1_utils.h"
#include "token_step-1.c"
#include "token_step-2.c"
#include "free.c"
#include <valgrind/memcheck.h>
#include "execute.c"
#include "redirect.c"

/*****
 * 
 * 실행순서
 * 1. libft 폴더 내부에서 make bonus 실행 (o 파일은 gitignore되어있음)
 * 2. 0.1-main 내부에서 아래 명령어 실행
 * cc -g main.c token_step-1_utils.c libft/libft.a -lreadline
 *
 * 	맥북 실행시,
 * 1. readline 이슈, rl_clear_history()때문에 작동 불가 -> 주석처리 후 작업
 */

#include <errno.h>

unsigned char exitcode = 0;

void	init_minish(t_minish *sh)
{
	
	ft_memset(sh, 0, sizeof(t_minish));
	//main에서 받은 envps 저장
}

int		read_input(t_minish *sh)
{
	char 		*input;
	unsigned char exitcode;
	
	input = readline("minishell> ");
	if (input == NULL)
	{
		//todo: exitcode = 
		printf("%s\n","exit"); //todo: exit
		return (-1);
	}
	else if (ft_strlen(input) == 0) 
	{
		free(input); //todo: continue
		return (0);
	}
	add_history(input);
	sh->src = input;
	return (1);
}




int	**create_pipes(int child_num)
{
	int	**pp;
	int	i;

	pp = malloc(sizeof(int *) * (child_num - 1));
	i = 0;
	while (i < child_num - 1)
	{
		pp[i] = malloc(sizeof(int) * 2);
		if (pipe(pp[i]) < 0)
		{
			while (i >= 0)
				free(pp[i--]);
			free(pp);
			return (NULL);
		}
		i++;
	}
	return (pp);
}

void	set_pipe(int i, int **pipes, t_ready *rdy, int child_num)
{
	rdy->in_fd = STDIN_FILENO;
	if (i > 0)
		rdy->in_fd = pipes[i - 1][0];
	rdy->out_fd = STDOUT_FILENO;
	if (i < child_num - 1)
		rdy->out_fd = pipes[i][1];
}

pid_t	create_process(t_ready *rdy, int child_num, int **pipes)
{
	pid_t	pid;
	int		in_fd;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (redirect(&(rdy->rdrct), rdy) != 0);
			exit(EXIT_FAILURE);			
		execute_cmd(rdy);
	}
	else
	{
		//parents func()
		
	}	
}

int	execute(t_minish *sh)
{
	int	n;
	t_list	*lst;
	t_ready	*rdy;
	pid_t	*child_pids;
	int		**pipes;
	int		i;
	int		status;

	n = ft_lstsize(sh->ready);
	child_pids = malloc(sizeof(pid_t) * n);
	lst = sh->ready;
	pipes = create_pipes(n);
	i = 0;
	while (lst)
	{
		rdy = (t_ready *)(lst->content);
		set_pipe(i, pipes, rdy, n);
		create_process(rdy, i, pipes);
		i++;
		lst = lst->next;
	}

	//parent_process;
	i = 0;
	while (waitpid(child_pids[i], &status, 0))
	{
		i++;
	}
}

//cc -g main.c token_step-1_utils.c libft/libft.a -lreadline -o 1
int main(int ac, char **av, char **envp) 
{
	(void)ac;
	(void)av;
	t_minish	sh;

	set_signal(before_readline);
	init_minish(&sh);
	//init_minish(&sh, envp);
	while (true)
	{
		if (read_input(&sh) == 0)
			continue ;
		else if (read_input(&sh) == -1)
			break;
		if (!generate_mask(&sh) || !parsing(&sh, ft_strlen_delim(sh.mask, '\n')))
		{
			printf("exitcode:%d\n", exitcode);
			free_minish(&sh);
		 }
		execute(&sh);
		//verify_exitcode();
		// f_init_envps(&sh);
		//excute_commands(); //builtin&path_functions		
	}
    rl_clear_history();
	return 0;
}
