/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:26:42 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/02/23 19:38:59 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_main.h"
# include "token_step-1_utils.h"

//token_step-2_utils.c에 있는 함수 
// 추후 token_step-1_utils.h에 원형 업데이트시 아래 함수 삭제 해야함
void	del_text(void *txt)
{
	free((char *)txt);
	txt = NULL;
}

char    **create_str_2(t_list **head)
{
    int size;
    char    **str;
    t_list  *tmp;
	int	i;
    
	size = ft_lstsize(*head);
    str = malloc(sizeof(char *) * (size + 1));
	i = 0;
	tmp = *head;
    while (i < size)
    {
        str[i] = ft_strdup((char *)tmp->content);
		i++;
		tmp = tmp->next;
    }
    str[size] = NULL;
	ft_lstclear(head, del_text);
	return (str);
}