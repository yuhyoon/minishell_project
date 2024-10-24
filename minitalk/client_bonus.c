/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:08:19 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/08/13 13:34:09 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	handler_ack(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("%s\n", "ACK");
	exit(0);
}

void	send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (0x001 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(450);
		bit++;
	}
}

int	check_pid(char *pid, int ipid)
{
	if (*pid == '0')
	{
		ft_printf("%s\n", "PID ERROR : Do not start with number 0");
		return (-1);
	}
	if (ipid < 0)
	{
		ft_printf("%s\n", "PID ERROR [USE Negative NUM]: Can NOT use under 0");
		return (-1);
	}
	if (4194304 <= ipid)
	{
		ft_printf("%s\n", "PID ERROR [Over MaxPID]: Use under 4194304(Max pid)");
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*msg;

	pid = 0;
	if (argc == 3)
	{
		pid = ft_atoi(*(argv + 1));
		if (check_pid(argv[1], pid) == -1)
			return (0);
		signal(SIGUSR1, handler_ack);
		msg = *(argv + 2);
		while (*msg != 0)
		{
			send_bits(pid, *msg);
			msg++;
		}
		send_bits(pid, '\0');
	}
	else
		ft_printf("%s\n", "Error : Try ./client [PID] [Msg]");
	return (0);
}
