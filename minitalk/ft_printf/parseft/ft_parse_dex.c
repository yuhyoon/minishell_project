/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:13:24 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/08/12 20:52:06 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseft.h"

void	parse_dex(va_list ap, char *strs, int *total)
{
	int				d;
	char			*s;
	char			*head;
	unsigned int	u;

	s = NULL;
	if (*strs == 'd' || *strs == 'i')
	{
		d = va_arg(ap, int);
		s = ft_itoa(d);
	}
	else if (*strs == 'u')
	{
		u = va_arg(ap, unsigned int);
		s = ft_itou(u);
	}
	head = s;
	while (*s)
	{
		write(1, s, 1);
		(*total)++;
		s++;
	}
	free(head);
}
