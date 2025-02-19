#include "parse_main.h"
# include "token_step-1_utils.h"
#include "token_step-1.c"
#include "token_step-2.c"

/*****
 * 
 * 실행순서
 * 1. libft 폴더 내부에서 make bonus 실행 (o 파일은 gitignore되어있음)
 * 2. 0.1-main 내부에서 아래 명령어 실행
 * cc -g main.c token_step-1_utils.c libft/libft.a -lreadline
 *
 * 	맥북 실행시,
 * 1. readline 이슈,
 */

// void	change_exit_status(int exit_status)
// {
// 	if (exit_status)
		
// }
// #include <sys/stat.h>
#include <errno.h>
// #include <stdlib.h>
// #include <stdio.h>


// ctrl-C 시그널을 처리할 핸들러
void handle_ctrl_c(int sig)
{
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_ctrl_back(int sig)
{
	// cat grep 과 같이 
	// ft_putstr_fd("\n", 2);
	return ;	
}


// 시그널 핸들러 설정
void set_signal()
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_back); 
}


int main() 
{
	char *input;
	char	*mask;
	t_list	*rdy_head;

	while (1) 
	{
		set_signal();
		input = readline("minishell> ");
		
		if (input != NULL) 
		{
			add_history(input);
			mask = generate_mask(input);
			rdy_head = parsing(input, mask, ft_strlen_delim(mask, '\n'));
			// printf("\n입력이 널이면 종료\n");
			// break;
		}
		else
		{
			printf("%s\n","ctrl + D");
			break;
		}
		if (ft_strlen(input) == 0) 
		{
			free(input);
			continue;
		}
		// 	free(mask);
		// 	free(input);
	}
	// rl_clear_history();
	
	return 0;
}
