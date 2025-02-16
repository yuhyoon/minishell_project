/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:48 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/03/25 17:39:54 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	size_t	cnt;

	cnt = 0;
	if (!lst)
		return (0);
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		cnt++;
	}
	return (cnt);
}
