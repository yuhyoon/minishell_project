/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:38:42 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/07/26 10:39:05 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s1, const char *s2)
{
	char	*ss1;
	char	*ss2;
	size_t	cnt;

	ss1 = (char *)s1;
	ss2 = (char *)s2;
	cnt = 0;
	while (*s1)
	{
		if (ft_strchr(ss2, *ss1) != NULL)
		{
			cnt++;
			s1++;
		}
		else
			return (cnt);
	}
	return (cnt);
}
