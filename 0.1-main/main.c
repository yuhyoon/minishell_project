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
 * 1. readline 이슈, rl_clear_history()때문에 작동 불가 -> 주석처리 후 작업
 */

#include <errno.h>

void	before_readline(int signal)
{
	if (signal == SIGINT)
	{
		//버퍼 삭제... (이걸로 되려나..)
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		//종료 값 설정
	}
	//없어도 될 것 같지만 차일을 위해 남겨둠
	// else if (signal == SIGQUIT)
	// {
	// 	(void)signal;
	// }
}

void	set_signal(void *handler)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

int main() 
{
	char 		*input;
	char		*mask;
	t_list		*rdy_head;
	// t_exe_info 	*converted;

	while (1) 
	{
		set_signal(before_readline);
		input = readline("minishell> ");
		if (input == NULL)
		{
			//cat grep에서는 다르게 동작함 (그건 fork 후에 처리하는 구간에서 추가)
			printf("%s\n","exit");
			break;
		}
		add_history(input);
		mask = generate_mask(input);
		rdy_head = parsing(input, mask, ft_strlen_delim(mask, '\n'));
		if (ft_strlen(input) == 0) 
		{
			free(input);
			continue;
		}
		// 	free(mask);
		// 	free(input);
	}
    rl_clear_history();
	return 0;
}
