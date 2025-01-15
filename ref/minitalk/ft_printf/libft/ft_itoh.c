/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:51:47 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/04/20 18:57:17 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_hex(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		i++;
	while (nbr != 0)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}

static void	set_hex(char *strs, unsigned int nbr, int count, int flag)
{
	int		remainder;

	remainder = 0;
	if (nbr == 0)
		strs[0] = '0';
	while (nbr != 0)
	{
		remainder = nbr % 16;
		if (remainder > 9)
			strs[--count] = remainder + flag;
		else
			strs[--count] = remainder + '0';
		nbr = nbr / 16;
	}
}

char	*ft_itoh(unsigned int nbr, int flag)
{
	char			*strs;
	int				count;

	count = count_hex(nbr);
	strs = (char *)malloc(sizeof(char) * (count + 1));
	if (!strs)
		return (NULL);
	strs[count] = '\0';
	set_hex(strs, nbr, count, flag);
	return (strs);
}
