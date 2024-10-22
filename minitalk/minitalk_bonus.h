/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:46:56 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/08/12 19:56:44 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include "ft_printf/parseft/parseft.h"

int		ft_atoi(const char *str);
void	handler_ack(int sig);
void	send_bits(int pid, char i);
void	handler_sigaction(int sig, siginfo_t *info, void *context);

#endif