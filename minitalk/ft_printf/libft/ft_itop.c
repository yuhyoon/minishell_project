/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:24:31 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/04/20 18:58:07 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_hex(unsigned long nbr)
{
	int	i;

	i = 0;
	while (nbr != 0)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}

static void	set_hex(char *strs, unsigned long nbr, int count)
{
	int		remainder;

	remainder = 0;
	if (nbr == 0)
		strs[0] = '0';
	while (nbr != 0)
	{
		remainder = nbr % 16;
		if (remainder > 9)
			strs[--count] = remainder + 87;
		else
			strs[--count] = remainder + '0';
		nbr = nbr / 16;
	}
}

char	*ft_itop(unsigned long n)
{
	char		*strs;
	int			count;

	count = count_hex(n);
	strs = (char *)malloc(sizeof(char) * (count + 1));
	if (!strs)
		return (NULL);
	strs[count] = '\0';
	set_hex(strs, n, count);
	return (strs);
}
