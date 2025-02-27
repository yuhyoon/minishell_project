#include "main.h"
#include "parse_main.h"
#include "delete.h"
#include "error.h"

char    **create_str_2(t_list **head)
{
    int size;
    char    **str;
    t_list  *tmp;
	int	i;
    
	size = ft_lstsize(*head);
    str = malloc(sizeof(char *) * (size));
	i = 0;
	tmp = *head;
    while (i < size)
    {
        str[i] = ft_strdup((char *)tmp->content);
		i++;
		tmp = tmp->next;
    }
	ft_lstclear(head, del_text);
	return (str);
}

int valid_rdrct(t_ready *rdy)
{
    t_list	*lst;
	t_redrct	*rdrct;
	int		n;

	lst = rdy->rdrct;
	errno = 0;
	n = rdy->rdrct_num;
	printf("valid_rdrct\n");
	while (n && errno == 0)
	{
		rdrct = (t_redrct *)(lst->content);
		printf("first rdrct obj:%s", rdrct->obj);
		access(rdrct->obj, F_OK);
		printf("errno: %d\n", errno);
		if (errno != 0)
			err_such(1, rdrct);
		if (errno == 0 && rdrct->type == IN_RD && access(rdrct->obj, R_OK) != 0)
			err_permission(1, rdrct);
		else if (errno == 0 && rdrct->type == OUT_RD && access(rdrct->obj, W_OK) != 0)
			err_permission(1, rdrct);
		lst = lst->next;
		n--;
	}

	return (errno);
}

int execute_cmd(t_ready	*rdy)
{
    char	**cmd;
	char	*name;

	cmd = create_str_2(&rdy->text);
	name = cmd[0];
	printf("%s\n", name);   
	close(pp[0]);
	if (dup2(pp[1], STDOUT_FILENO) == -1)
		error_exit_errno("dup2 error");
	close(pp[1]);
	if (execve(f_p, cmd, NULL) == -1)
		exit(EXIT_FAILURE);
    
}
