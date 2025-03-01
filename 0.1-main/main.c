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
#include <stdio.h>

int f_double_array_size(char **array) //utils에 넣으면 좋겠음!
{
    int size;

	size = 0;
    while (array[size] != NULL)
        size++;
    return (size);
}

void	init_minish(t_minish *sh, char **envp)
{
	int	envps_size;
	int envp_len;
	int i;

	ft_memset(sh, 0, sizeof(t_minish));
	envps_size = f_double_array_size(envp);
	sh->envp = (char **)malloc(sizeof(char *) * (envps_size + 1));
	if (!sh->envp)
		return ;
	i = -1;
	while (envp[++i] != NULL)
	{
		envp_len = ft_strlen(envp[i]);
		sh->envp[i] = (char *)malloc(sizeof(char) * (envp_len + 1));
		if (!sh->envp[i])
		{
			free_str_array(sh->envp);
			return ;
		}
	}
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

//cc -g main.c token_step-1_utils.c libft/libft.a -lreadline -o 1
int main(int ac, char **av, char **envp) 
{
	(void)ac;
	(void)av;
	t_minish	sh;

	set_signal(before_readline);
	init_minish(&sh, envp);
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
		//verify_exitcode();
		// f_init_envps(&sh);
		//excute_commands(); //builtin&path_functions		
		// free_minish(&sh); ??
	}
    rl_clear_history();
	return 0;
}
