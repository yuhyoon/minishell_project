#include "analysis.h"

t_redrct	*init_rdrct(void)
{
	t_redrct	*rdrct;

	rdrct = malloc(sizeof(t_redrct));
	ft_memset(rdrct, 0, sizeof(rdrct));
	return (rdrct);
}

int create_rdrct(char *src, char *mask, t_list **head)
{
    int i;
	t_redrct	*new;
	char	*str;
	int		len;
	t_list	*lst;

	lst = ft_lstnew(init_rdrct());
    i = 0;
	new = ((t_redrct *)((lst)->content));
	new->type = mask[i];
    while (mask[i] == new->type)
        i++;
	new->parts = i;
	while (mask[i] == NONE)
		i++;
	len = count_text(&mask[i]);
	ft_memset(&mask[i], new->type, len);
	str = malloc(sizeof(char) * (len + 1));
	str = ft_memcpy(str, &src[i], len);
	str[len] = '\0';
	new->obj = str;
	ft_lstadd_back(head, lst);
	return (i + len);
}
