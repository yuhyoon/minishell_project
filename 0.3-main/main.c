#include "main.h"
#include "parse.h"
#include "parse_step.h"
#include "analysis.h"
#include "execution.h"
#include "error.h"
#include "free.c"
#include "child_process.h"
#include "child_process.c"

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

int exitcode = 0;

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

// void	set_pipe_old(int i, int *pipes, t_ready *rdy, t_minish *sh)
// {
// 	rdy->input = STDIN_FILENO;
// 	if (sh->prev_for_pipe != -1)
// 	{
// 		dup2(sh->prev_for_pipe, rdy->input);
// 		close(sh->prev_for_pipe);
// 	}
// 	if (rdy->rdrct_in)
// 	{
// 		dup2(rdy->rdrct_in->fd, rdy->input); //n copy to rdy->input;
// 		close(rdy->rdrct_in->fd);
// 	}
// 	rdy->output = STDOUT_FILENO;
// 	if (rdy->rdrct_out)
// 	{
// 		dup2(rdy->rdrct_out->fd, rdy->output); //n copy to rdy->input;
// 		close(rdy->rdrct_out->fd);
// 	}
// 	if (rdy->num < sh->cmd_count)
// 	{
// 		dup2(pipes[1], rdy->output);
// 		close(pipes[1]);
// 		close(pipes[0]);
// 	}
// }

// void	child_process_old(t_ready *rdy, int *pp, t_minish *sh)
// {
// 	if (valid_rdrct(rdy) != 0 || redirect(&(rdy->rdrct), rdy) != 0)
// 		del_ready(rdy);
// 	if (rdy == NULL)
// 	{
// 		if (pp != NULL)
// 		{
// 			close(pp[0]);
// 			close(pp[1]);
// 		}
// 		exit(EXIT_FAILURE);
// 	}
// 	//set_pipe_old(pp, rdy, sh);
// 	rdy->cmd = create_str_2(&rdy->text);
// 	if (is_builtin(rdy->cmd[0]))
// 		printf("here builtin\n");
// 	else
// 	{
// 		char *access_path = get_acesspath(rdy, pp);
// 		if (access_path == NULL)
// 		{
// 			err_exec(127, rdy->cmd[0]);
// 			del_ready(rdy);
// 			free(access_path);
// 			access_path = NULL;
// 			exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			if (execve(access_path, &rdy->cmd[0], NULL) == -1)
// 				exit(EXIT_FAILURE);
// 		}
// 	}
// }


bool	is_builtin(char *cmd_name)
{
	return (false);
}

void	close_pp(t_child_process *child, t_minish *sh)
{
	if (child->num < sh->cmd_count)
	{
		close(child->pp[0]);
		close(child->pp[1]);
	}
}
void    child_process_handle(t_child_process *child, t_ready *rdy, t_minish *sh)
{
	if (child->state == STATE_COMPLETE)
		del_ready(rdy);
	else if (child->state == STATE_CHECK_RDRCT || child->state == STATE_CHECK_PIPE)
		close_pp(child, sh);
	else if (child->state == STATE_CHECK_CMD)
		err_exec(127, child->cmd[0]);
}

void	valid_exepath(t_child_process *child, t_ready *rdy)
{
	child->cmd = create_str_2(&rdy->text);
	if (is_builtin(child->cmd[0]) == true)
	{
		child->state = STATE_EXEC_BUILTIN;
		return ;
	}
	child->exe_path = find_exepath(child->cmd[0]);
	if (child->exe_path == NULL)
	{
		del_ready(rdy);
		dengling(child->exe_path, 1);
		return ;
	}
	child->state = STATE_EXEC_CMD;
}
void	init_child_process(t_child_process *child, int *pp, t_ready *rdy, t_minish *sh)
{
	child->num = rdy->num;
	child->pp = pp;
	child->cmd = NULL;
	child->input_fd = STDIN_FILENO;
	// if (sh->cmd_count > 1 && child->num < sh->cmd_count)
	// 	child->input_fd = sh->prev_for_pipe;
	child->output_fd = STDOUT_FILENO;
	child->exe_path = NULL;
	if (rdy->rdrct != NULL)
		child->state = STATE_CHECK_RDRCT;
	else
		child->state = STATE_CHECK_CMD;
}
void	valid_redirect(t_child_process *child, t_ready *rdy)
{
	if (valid_rdrct(rdy) != 0 || redirect(&(rdy->rdrct), rdy) != 0)
		del_ready(rdy);
	else
	{
		child->state = STATE_CHECK_CMD;
	}
}

void	set_pipe(t_child_process *child, t_minish *sh, t_ready *rdy)
{
	if (sh->prev_for_pipe != -1)
	{
		dup2(sh->prev_for_pipe, child->input_fd);
		close(sh->prev_for_pipe);
	}
	if (child->num < sh->cmd_count && sh->cmd_count > 1)
	{
		dup2(child->pp[1], child->output_fd);
		close(child->pp[1]);
		close(child->pp[0]);
	}
	child->state = STATE_EXEC_CMD;
}

void	execute_cmd(t_child_process *child)
{
	if (execve(child->exe_path, &child->cmd[0], NULL) != -1)
		child->state = STATE_COMPLETE;
}

int	child_process(t_ready *rdy, int *pp, t_minish *sh)
{
	t_child_process	child;

	init_child_process(&child, pp, rdy, sh);
	while (rdy != NULL && child.state < STATE_COMPLETE)
	{
		if (child.state == STATE_CHECK_RDRCT)
			valid_redirect(&child, rdy);
		else if (child.state == STATE_CHECK_CMD)
			valid_exepath(&child, rdy);
		else if (child.state == STATE_EXEC_BUILTIN)
			printf("exec_bulitin(rdy, sh, &child)\n");
		else if (child.state == STATE_CHECK_PIPE)
			set_pipe(&child, sh, rdy);
		else if (child.state == STATE_EXEC_CMD)
			execute_cmd(&child);
	}
	child_process_handle(&child, rdy, sh);
	return (child.state);
}

pid_t	create_process(t_ready *rdy, t_minish *sh)
{
	pid_t	pid;

	int		status;
	int		pp[2];

	if (rdy->num < sh->cmd_count)
		pipe(pp); //todo: err handling
	else
		pp = NULL;
	pid = fork();
	if (pid == 0)
	{
		child_process(rdy, pp, sh);
	}
	else
	{
		sh->child_pids[rdy->num - 1] = pid;
		if (sh->prev_for_pipe != -1)
			close(sh->prev_for_pipe);
    	if (sh->cmd_count > 1 && rdy->num < sh->cmd_count)
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

	sh->cmd_count = ft_lstsize(sh->ready);
	sh->child_pids = malloc(sizeof(pid_t) * sh->cmd_count);
	lst = sh->ready;
	while (lst)
	{
		rdy = (t_ready *)(lst->content);
		create_process(rdy, sh);
		lst = lst->next;
	}
	i = 0;
	while (i < sh->cmd_count)
	{
		if (i == sh->cmd_count - 1)
			exitcode = WEXITSTATUS(status);
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


