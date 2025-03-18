#include "main.h"
#include "parse.h"
#include "parse_step.h"
#include "analysis.h"
#include "execution.h"
#include "error.h"
#include "free.h"
#include "child_process.h"

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

// void    f_init_envps(t_minish *sh)
// {
//     t_envp **n_envps;
//     t_envp *sorted_envps;

//     n_envps = (t_envp **)malloc(sizeof(t_envp *));
//     sorted_envps= NULL;
//     f_init_env(sh->envp, sh->n_envs);
//     f_sort_and_store_envp(sh->envp, sh->n_export); //이름 변경
// }

void	init_minish(t_minish *sh, char **envp)
{
	int	result;

	sh->envp = NULL;
	sh->built_code = 0;
	ft_memset(sh, 0, sizeof(t_minish));
	if (!envp)
		return;
	result = init_envp(sh, envp);
	if (result == -1)
		return ;
}

int	read_input(t_minish *sh)
{
	char	*input;

	input = readline("minishell> ");
	if (input == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (0);
	}
	else if (ft_strlen(input) == 0)
	{
		// printf("%ld\n", ft_strlen(input));
		free(input); // todo: continue
		return (2);
	}
	add_history(input);
	sh->src = ft_strdup(input);
	add_history(sh->src);
	free(input);
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

pid_t	create_process(t_ready *rdy, t_minish *sh)
{
	pid_t	pid;
	int		result;
	int		pp[2];

	if (rdy->num < sh->cmd_count)
		pipe(pp); // todo: err handling
	pid = fork();
	if (pid == 0)
	{
		result = child_process(rdy, pp, sh);
		//	result = 0;
		printf("child result:%d\n", result);
		exit(result);
	}
	else
	{//printf("@@@ rdy->num: %d@@@\n", rdy->num);
		if (sh->child_pids != NULL)
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

// int    execute_single_builtin(int bulitin_code, char **cmds, t_minish *sh)
int	execute_single_builtin(int bulitin_code, t_minish *sh) //sh->ready->content->cmd (char **)
{
	int	res;

	res = -1;
	if (bulitin_code == 1)
		res = f_cd(sh);
    else if (bulitin_code == 2)
        res = f_echo(sh);            
    else if (bulitin_code == 3)
        res = f_pwd(sh);            
    else if (bulitin_code == 4)
        res = f_export(sh);            
    else if (bulitin_code == 5)
        res = f_env(sh);            
    else if (bulitin_code == 6)
        res = 0; //f_unset
    else if (bulitin_code == 7)
        res = f_exit(sh);
	//정상종료일때랑 아닐때
    return (res);
}

int	execute_single_is_builtin(t_list *lst, t_minish *sh)
{
	t_ready	*rdy;
	int		i;
	int		bulitin_code;
	int		result;

	rdy = (t_ready *)(lst->content);
	i = 0;
	bulitin_code = is_builtin(rdy->cmd[0]);
	result = bulitin_code;
	if (bulitin_code != 0) //bulitin이 아니면 result 0으로 종료
	{
		result = execute_single_builtin(bulitin_code, sh);
		if (result == 0)
			result = bulitin_code; //정상종료 된 bulitin
		else
			result = -1; //비정상 종료
	}	
	return (result);
}

//printf 지워도 30줄
int	execute(t_minish *sh)
{
	t_list		*lst;
	t_ready		*rdy;
	int 		i;
	int 		status;

	sh->cmd_count = ft_lstsize(sh->ready);
	//printf("### cmd_count:%d\n", sh->cmd_count);
	sh->child_pids = malloc(sizeof(pid_t) * sh->cmd_count);
	lst = sh->ready;
	if (sh->cmd_count == 1)
	{
		//free_minish->memset이 기존 evnp 변수들 다 지움
		sh->built_code = execute_single_is_builtin(lst, sh);
	}
	if (sh->built_code == 0)
	{
		//printf("***child_pids %ld***\n", sh->child_pids[i]);	
		waitpid(sh->child_pids[i], &status, 0);
		 if (i == sh->cmd_count - 1)
		 {
		 	exitcode = WEXITSTATUS(status);
		 	//printf("exitcode: %d\n", exitcode);
		 }
		i++;
	}
	free_minish(sh);
}

void	free_init_envps(t_minish *sh)
{
	if (sh->pwd)
		free(sh->pwd);
	free_double_char(sh->envp);
	free_envps(&(sh->n_envs));
	free_envps(&(sh->n_export));
}

// cc -g main.c token_step-1_utils.c libft/libft.a -lreadline -o 1
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_minish	sh;
	int			res;

	set_signal(before_readline);
	init_minish(&sh, envp);
	while ((res = read_input(&sh)))
	{
		if (res == 1)
		{
		if (!generate_mask(&sh) || !parsing(&sh, ft_strlen_delim(sh.mask, '\n')))
		{
			//printf("exitcode:%d\n", exitcode);
			free_minish(&sh);
		}
		// verify_exitcode();
	}
	// if (&(sh.pwd))
	// 	free(sh.pwd);
	free_init_envps(&sh);
	// ft_memset(&sh, 0, sizeof(t_minish));
	// free_minish()
	rl_clear_history();
	return (0);
}
