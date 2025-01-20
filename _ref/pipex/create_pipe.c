/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:42:23 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/07/26 14:42:33 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(t_fds *fds)
{
	if (pipe(fds->pp) == -1)
		error_exit_errno("something error in pipe");
	dup2(fds->in_fd, STDIN_FILENO);
}
