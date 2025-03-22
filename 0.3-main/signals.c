/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:55:43 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/22 10:37:11 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


void	do_sigint_heredoc(int signum)
// heredoc에서 crtl+c 시그널 입력시 줄바꿈을 출력하고 1을 반환하며 종료됨
{
	(void)signum;
	
	write(STDERR_FILENO, "\n", 1);
	// 줄바꿈을 출력
	// write(STDERR_FILENO, "\n", 1);
	exit (1); // 1 을 반환하며 종료
}

void	set_signal_heredoc(void)
// heredoc을 실행하는 프로세스의 시그널 동작을 설정해줌
{
	signal(SIGINT, do_sigint_heredoc); // ctrl+c 시그널 입력시 do_sigint_heredoc함수 실행
	signal(SIGQUIT, SIG_IGN); // ctrl+\ 시그널 입력시 시그널을 무시함
}

void	set_signal_fork(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

//unistd.h -> STDERR_FILENO
void	before_readline(int signal)
{
	if (signal == SIGINT)
	{
		//버퍼 삭제... (이걸로 되려나..)
		write(STDERR_FILENO, "\n", 1);
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

// void	during_heredoc(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		write(1, )
// 	}
// }

// void	set_heredoc_signal(void *handler)
// {
// 	during_heredoc(SIGINT, )
// }

void	set_signal(void *handler)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
