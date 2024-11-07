/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:19:31 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/08/07 00:13:00 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_text(char *strs, int *total)
{
	write(1, strs, 1);
	(*total)++;
}

void	parse_value(va_list ap, char *strs, int *total)
{
	if (*strs == 'c')
		parse_char(ap, total);
	else if (*strs == 's')
		parse_str(ap, total);
	else if (*strs == 'p')
		parse_pointer(ap, total);
	else if (*strs == 'x' || *strs == 'X')
		parse_hex(ap, strs, total);
	else if (*strs == 'd' || *strs == 'i' || *strs == 'u')
		parse_dex(ap, strs, total);
	else if (*strs == '%')
		parse_text(strs, total);
}

int	ft_printf(const char *strs, ...)
{
	va_list	ap;
	int		total;

	va_start(ap, strs);
	total = 0;
	while (*strs)
	{
		if (*strs == '%')
		{
			strs++;
			parse_value(ap, (char *)strs, &total);
		}
		else
			parse_text((char *)strs, &total);
		strs++;
	}
	va_end(ap);
	return (total);
}
