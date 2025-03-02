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
	sh->prev_for_pipe = -1;
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

void	set_pipe(int i, int *pipes, t_ready *rdy, t_minish *sh)
{
	rdy->input = STDIN_FILENO;
	if (sh->prev_for_pipe != -1)
	{
		dup2(sh->prev_for_pipe, rdy->input);
		close(sh->prev_for_pipe);
	}
	if (rdy->rdrct_in)
	{
		dup2(rdy->rdrct_in->fd, rdy->input); //n copy to rdy->input;
		close(rdy->rdrct_in->fd);
	}
	rdy->output = STDOUT_FILENO;
	if (rdy->rdrct_out)
	{
		dup2(rdy->rdrct_out->fd, rdy->output); //n copy to rdy->input;
		close(rdy->rdrct_out->fd);
	}
	if (i + 1 < sh->cmd_num)
	{
		dup2(pipes[1], rdy->output);
		close(pipes[1]);
		close(pipes[0]);
	}
}

pid_t	create_process(t_ready *rdy, int i, t_minish *sh)
{
	pid_t	pid;

	int		status;
	int		pp[2];

	if (i + 1 < sh->cmd_num)
		pipe(pp); //todo: err handling
	pid = fork();
	if (pid == 0)
	{
		if (redirect(&(rdy->rdrct), rdy) != 0)
			exit(EXIT_FAILURE);
		set_pipe(i, pp, rdy, sh);
		execute_cmd(rdy, pp);
	}
	else
	{
		sh->child_pids[i] = pid;
		if (sh->prev_for_pipe != -1)
			close(sh->prev_for_pipe);
    	if (i + 1 < sh->cmd_num)
		{
        	close(pp[1]);
    		sh->prev_for_pipe = pp[0];
		}
	}	
}

int	execute(t_minish *sh)
{
	t_list	*lst;
	t_ready	*rdy;
	int		i;
	int		status;

	sh->cmd_num = ft_lstsize(sh->ready);
	sh->child_pids = malloc(sizeof(pid_t) * sh->cmd_num);
	lst = sh->ready;
	i = 0;
	while (lst)
	{
		rdy = (t_ready *)(lst->content);
		create_process(rdy, i, sh);
		i++;
		lst = lst->next;
	}
	i = 0;
	while (i < sh->cmd_num)
	{
		waitpid(sh->child_pids[i], &status, 0);
		i++;
	}
	free_minish(sh);
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
