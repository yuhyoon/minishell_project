/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:31:07 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/04/20 18:57:46 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_unsigned(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr <= 0)
		i++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

static void	set_unsigned(char *strs, unsigned int nbr, int count)
{
	int		remainder;

	remainder = 0;
	if (nbr == 0)
		strs[0] = '0';
	while (nbr != 0)
	{
		remainder = nbr % 10;
		strs[--count] = remainder + '0';
		nbr = nbr / 10;
	}
}

char	*ft_itou(int n)
{
	int				count;
	char			*strs;
	unsigned int	nbr;

	nbr = n;
	count = count_unsigned(nbr);
	strs = (char *)malloc(sizeof(char) * (count + 1));
	if (!strs)
		return (NULL);
	strs[count] = '\0';
	set_unsigned(strs, nbr, count);
	return (strs);
}
