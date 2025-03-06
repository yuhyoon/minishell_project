#include "execution.h"
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

char	**create_str_2(t_list **head)
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
	str[i] = NULL;
	ft_lstclear(head, del_text);
	return (str);
}

char	*find_exepath(char *name)
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

char	*get_acesspath(t_ready *rdy, int *pipe)
{
	char	*name;
	char	*exe_path;

	name = (rdy->cmd[0]);
	//printf("%s\n", *name);   
	exe_path = find_exepath(rdy->cmd, name);
	return (exe_path);
}