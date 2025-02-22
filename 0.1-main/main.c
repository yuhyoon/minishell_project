#include "main.h"
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

unsigned char exitcode;

void	before_readline(int signal)
{
	if (signal == SIGINT)
	{
		//버퍼 삭제... (이걸로 되려나..)
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		//exitcode 
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
		//exitcode = 
		printf("%s\n","exit"); //todo: exit
		return (-1);
	}
	else if (ft_strlen(input) == 0) 
	{
		free(input); //todo: continue
		return (0);
	}
	add_history(input);
	sh->input = input;
	return (1);
}

//cc -g main.c token_step-1_utils.c libft/libft.a -lreadline -o 1
int main() 
{
	t_minish	sh;

	set_signal(before_readline);
	exitcode = 0;
	init_minish(&sh);
	while (true)
	{
		if (read_input(&sh) == 0)
			continue ;
		else if (read_input(&sh) == -1)
			break;
		if (!generate_mask(sh.input) || !parsing(sh.input, sh.mask, ft_strlen_delim(sh.mask)))
			clean_minish(&sh);
		//verify_exitcode();
		//f_init_envps();
		//excute_commands(); //builtin&path_functions		
	}
    rl_clear_history();
	return 0;
}
