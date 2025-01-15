/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:06:18 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/08/12 20:52:19 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseft.h"

void	parse_hex(va_list ap, char *strs, int *total)
{
	int		d;
	char	*s;
	char	*head;

	s = NULL;
	if (*strs == 'x')
	{
		d = va_arg(ap, int);
		s = ft_itoh(d, 87);
	}
	else if (*strs == 'X')
	{
		d = va_arg(ap, int);
		s = ft_itoh(d, 55);
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
