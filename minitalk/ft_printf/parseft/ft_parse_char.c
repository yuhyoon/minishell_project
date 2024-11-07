/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:05:27 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/04/20 19:14:46 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseft.h"

void	parse_char(va_list ap, int *total)
{
	unsigned char	s;

	s = (unsigned char)va_arg(ap, int);
	write(1, &s, 1);
	(*total)++;
}

void	parse_str(va_list ap, int *total)
{
	char	*s;

	s = va_arg(ap, char *);
	if (s != 0)
	{
		while (*s)
		{
			write(1, s, 1);
			(*total)++;
			s++;
		}
	}
	else
	{
		write(1, "(null)", 6);
		*total += 6;
	}
}
