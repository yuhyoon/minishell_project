#include "main.h"
#include "parse_main.h"
#include "delete.h"
#include "error.h"

void	free_splited(char **abs)
{
	int	i;

	i = 0;
	if (!abs)
		return ;
	while (abs[i] != NULL)
	{
		free(abs[i]);
		abs[i] = NULL;
		i++;
	}
	free(abs[i]);
	abs[i] = NULL;
	free(abs);
	abs = NULL;
}

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

char	*create_exepath(char **cmd, char *name)
{
	char	**env_paths;
	int		i;
	char	*cmd_path;
	char	*exe_path;

	env_paths = ft_split(getenv("PATH"), ':');
	cmd_path = ft_strjoin("/", name);
	i = 0;
	while (env_paths[i] != NULL)
	{
		exe_path = ft_strjoin(env_paths[i], cmd_path);
		if (access(exe_path, X_OK) == 0)
			break ;
		free(exe_path);
		exe_path = NULL;
		i++;
	}
	free_splited(env_paths);
	free(cmd_path);
	cmd_path = NULL;
	return (exe_path);
}

int execute_cmd(t_ready	*rdy, int *pipe)
{
    char	**cmd;
	char	**name;
	char	*exe_path;

	cmd = create_str_2(&rdy->text);
	name = &cmd[0];
	printf("%s\n", *name);   
	exe_path = create_exepath(cmd, cmd[0]);
    if (execve(exe_path, name, NULL) == -1)
		exit(EXIT_FAILURE);
}
