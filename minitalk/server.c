/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:21:54 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/08/13 13:51:32 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_sigaction(int sig, siginfo_t *info, void *context)
{
	static int		bits;
	static int		idx;

	(void)context;
	(void)info;
	if (sig == SIGUSR1)
		idx = idx | (0x001 << bits);
	bits++;
	if (bits == 8)
	{
		ft_printf("%c", idx);
		bits = 0;
		idx = 0;
	}
}

void	ft_error(int idx)
{
	if (idx == 1)
		ft_printf("%s\n", "Sending ERROR (SIGUSR1)");
	else
		ft_printf("%s\n", "Sending ERROR (SIGUSR2)");
}

int	check_argc(int ac)
{
	if (ac > 1)
	{
		ft_printf("%s\n", "Type in the ONLY Execution file. try again.");
		return (-1);
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	int					pid;
	struct sigaction	sa;

	(void)argv;
	if (check_argc(argc) == -1)
		return (0);
	pid = getpid();
	ft_printf("pid : %d \n", pid);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler_sigaction;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_error(1);
		return (0);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_error(2);
		return (0);
	}
	while (1)
		pause();
	return (0);
}
