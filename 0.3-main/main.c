#include "main.h"
#include "parse.h"
#include "parse_step.h"
#include "analysis.h"
#include "execution.h"
#include "error.h"
#include "free.c"

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
	int	envp_length;
	int	i;

	envp_length = f_count_char(envp);
	ft_memset(sh, 0, sizeof(t_minish));
	sh->prev_for_pipe = -1;
	sh->envp = (char **)malloc(sizeof(char *) * (envp_length + 1)); //main에서 받은 envps 저장
	if (!(sh->envp))
		return ;
	i = -1;
	while (++i < envp_length)
		sh->envp[i] = ft_strdup(envp[i]);
	f_init_env(sh->envp, &(sh->n_envs)); //env node
	f_sort_and_store_envp(sh->envp, &(sh->n_export));  //export node
}


int		read_input(t_minish *sh)
{
	char 		*input;
	unsigned char exitcode;
	
	input = readline("minishell> ");
	if (input == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (0);
	}
	else if (ft_strlen(input) == 0) 
	{
		printf("%ld\n", ft_strlen(input));
		free(input); //todo: continue
		return (2);
	}
	printf("%ld\n", ft_strlen(input));
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

int is_builtin(char *cmd_name, t_minish *sh)
{
	int	res;

	res = 1;
    if (ft_strncmp(cmd_name, "cd", 2) == 0)
        res = f_cd(sh);
    else if (ft_strncmp(cmd_name, "echo", 4) == 0)
        res = f_echo(sh);
    else if (ft_strncmp(cmd_name, "pwd", 3) == 0)
        res = f_pwd(sh);
	// else if (ft_strncmp(cmd_name, "export", 7) == 0)
	//     res = f_export(sh);
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
	    res = f_env(sh);
    // else if (ft_strncmp(cmd_name, "unset", 6) == 0)
    //     res = f_unset(sh);
    // else if (ft_strncmp(cmd_name, "exit", 4) == 0)
    //     res = f_exit(sh);
    return (res); //0정상종료 1 비정상종료
}

void	child_process(t_ready *rdy, int *pp, int i, t_minish *sh)
{
	if (valid_rdrct(rdy) != 0 || redirect(&(rdy->rdrct), rdy) != 0)
		del_ready(rdy);
	if (rdy == NULL)
	{
		if (pp != NULL)
		{
			close(pp[0]);
			close(pp[1]);
		}
		exit(EXIT_FAILURE);
	}
	set_pipe(i, pp, rdy, sh);
	rdy->cmd = create_str_2(&rdy->text);
	if (is_builtin(rdy->cmd[0], sh) == 1) //0정상종료 1 비정상종료
	{
		char *access_path = get_acesspath(rdy, pp);
		if (access_path == NULL)
		{
			err_exec(127, rdy->cmd[0]);
			del_ready(rdy);
			free(access_path);
			access_path = NULL;
			exit(EXIT_FAILURE);
		}
		else
		{
			if (execve(access_path, &rdy->cmd[0], NULL) == -1)
				exit(EXIT_FAILURE);
		}
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
		child_process(rdy, pp, i, sh);
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

int execute_builtin(t_ready *rdy, t_minish *sh)
{
    if (is_builtin((char *)rdy->text->content, sh))
        return (0);// 빌트인 아님
    return (1); // 빌트인임
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
		if (sh->cmd_num == 1 && execute_builtin(rdy, sh) == 1)
			break;
		create_process(rdy, i, sh);
		i++;
		lst = lst->next;
	}
	//아래 부분 수정 WEXITSTATE
	// if (sh->cmd_num == 1 && execute_builtin(rdy, sh) == 1) 이 조건일땐 waitpid가 없어서 그 부분 처리도 해야함
	i = -1;
	while (++i < sh->cmd_num)
		waitpid(sh->child_pids[i], &status, 0);
	free_minish(sh); //main에서 처리하면 로직이 보여서 좋을듯 (꼭해야하는 이유가 있지 않다면)
}

//cc -g main.c token_step-1_utils.c libft/libft.a -lreadline -o 1
int main(int ac, char **av, char **envp) 
{
	(void)ac;
	(void)av;
	int	res;
	t_minish	sh;

	set_signal(before_readline);
	init_minish(&sh, envp);
	while ((res = read_input(&sh)))
	{
		if (res == 1)
		{
			if (!generate_mask(&sh) || !parsing(&sh, ft_strlen_delim(sh.mask, '\n')))
			{
				printf("exitcode:%d\n", exitcode);
				free_minish(&sh);
				return (1); //비정상 종료로 인식? bash 에서 프로그램 $? 했을 때 나올 수
			 }
			execute(&sh);
		}
		//verify_exitcode();
	}
	//free_minish()
    rl_clear_history();
	return (0);
}


