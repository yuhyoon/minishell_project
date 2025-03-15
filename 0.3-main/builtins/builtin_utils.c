/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/15 13:09:09 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <unistd.h>

int	f_count_char(char **envp)
{
	int count;

	count = 0;
	if (!envp)
		return (count); // envp가 NULL이면 0 반환
	while (envp[count] != NULL)
		count++;
	return (count);
}

void	free_double_char(char **double_char)
{
    int i;
    int length;

	i = -1;
	length = f_count_char(double_char);
	while (++i < length)
        free(double_char[i]);
    free(double_char); 
}

