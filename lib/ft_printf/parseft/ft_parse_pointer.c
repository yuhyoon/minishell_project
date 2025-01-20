/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:06:53 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/04/20 19:14:51 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseft.h"

void	parse_pointer(va_list ap, int *total)
{
	unsigned long	p;
	char			*s;
	char			*head;

	p = (unsigned long)va_arg(ap, char *);
	if (p != 0)
	{
		s = ft_itop(p);
		head = s;
		write(1, "0x", 2);
		(*total) += 2;
		while (*s)
		{
			write(1, s, 1);
			(*total)++;
			s++;
		}
		free(head);
	}
	else
	{
		write(1, "(nil)", 5);
		*total += 5;
	}
}
