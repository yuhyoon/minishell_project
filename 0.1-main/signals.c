/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:55:43 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/02/24 15:53:40 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	before_readline(int signal)
{
	if (signal == SIGINT)
	{
		//버퍼 삭제... (이걸로 되려나..)
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exitcode = 130;
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