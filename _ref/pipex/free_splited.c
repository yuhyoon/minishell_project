/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splited.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:36:27 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/07/26 10:51:06 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_splited(char **abs)
{
	int	i;

	i = 0;
	if (!abs)
		return ;
	while (abs[i] != NULL)
	{
		free(abs[i]);
		abs[i] = NULL;
		i++;
	}
	free(abs[i]);
	abs[i] = NULL;
	free(abs);
	abs = NULL;
}
