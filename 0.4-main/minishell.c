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
int g_shmode = 0;

void	init_minish(t_minish *sh)
{
	
	ft_memset(sh, 0, sizeof(t_minish));
	//main에서 받은 envps 저장
	sh->prev_for_pipe = -1;
}

int		read_input(t_ready *rdy)
{
	char 		*input;
	
	while (g_shmode == 0)
	{
		input = readline("minishell> ");
		if (input == NULL)
			g_shmode = -1;
		else if (ft_strlen(input) == 0)
			free(input);
		else
			g_shmode = PROMPT_OK;
	}
	if (g_shmode == PROMPT_OK)
	{
		add_history(input);
		rdy->src = input;
	}
	return (1);
}

void	*parse(t_list *cur_rdylst)
{
	t_ready	*rdy;
	t_list	*next_rdylst;
	char	*mask;

	rdy = (t_ready *)(cur_rdylst->content);
	mask = generate_mask(rdy);
	if (syntax_analysis(mask) > 0)
	{
		free(mask);
		mask = NULL;
		g_shmode = 12;
		rdy->exit_code = 2;
	}
	else
		rdy->mask = mask;
	if (g_shmode % 10 == 0)
		next_rdylst = parsing(cur_rdylst, ft_strlen_delim(rdy->mask, '\n'));
}

void    prompt(t_list *cur_rdylst, t_minish *sh)
{
    t_ready	*rdy;

	if (cur_rdylst == NULL)
	{
		cur_rdylst = ft_lstnew(create_rdy());
    	sh->ready = cur_rdylst;
	}	
	rdy = cur_rdylst->content;
    read_input(rdy);
}

void	handle_shmode(t_minish *sh)
{
	if (g_shmode % 10 != 0)
	{
		if (g_shmode < 0)
			exit(EXIT_SUCCESS);
		else if (g_shmode / 10 == 1)
			err_syntax(sh);
	}
	//sh->last_exit = ft_lstlast(sh->ready); //이거 나중에
	g_shmode = 0;
	
}

int main(int ac, char **av, char **envp) 
{
	(void)ac;
	(void)av;
	t_minish	sh;
    t_list     *cur_rdylst;

	set_signal(before_readline);
	init_minish(&sh);
    cur_rdylst = NULL; 
	while (g_shmode >= 0)
	{
		prompt(cur_rdylst, &sh);
		if (g_shmode == PROMPT_OK)
			cur_rdylst = parse(cur_rdylst);
		handle_shmode(&sh);
	}
    rl_clear_history();
	return 0;
}


