#include "main.h"
#include "parse_main.h"
# include "token_step-1_utils.h"
#include "token_step-1.c"
#include "token_step-2.c"
#include "free.c"
#include <valgrind/memcheck.h>

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

int	execute(t_minish *sh)
{
	int	n;
	t_list	*head;
	int pid;
    int first = 1;
    int status;
	int fds[2][2];

	head = sh->ready;
	while (head) 
    {
        if (head->next) {
            if (pipe(fds[1]) == -1) {
                printf("pipe error");
                exit(1);
            }
        }
        pid = fork();
        if (pid == -1) {
            printf("fork error");
            exit(2);
        }
        if (pid == 0) {
            if (!first) {
                dup2(fds[0][0], STDIN_FILENO);
                close(fds[0][0]);
                close(fds[0][1]);
            }
            if (head->next) {
                dup2(fds[1][1], STDOUT_FILENO);
                close(fds[1][0]);
                close(fds[1][1]);
            }

            execvp(head->cmd[0], head->cmd);
            // execve(path, head->cmd, environ);
            printf("execvp error");
            exit(3);
        }
        if (!first) {
            close(fds[0][0]);
            close(fds[0][1]);
        }
        if (head->next) {
            fds[0][0] = fds[1][0];
            fds[0][1] = fds[1][1];
        }
        first = 0;
        head = head->next;
    }
    while (wait(&status) > 0);

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
		execute();
		//verify_exitcode();
		// f_init_envps(&sh);
		//excute_commands(); //builtin&path_functions		
	}
    rl_clear_history();
	return 0;
}
