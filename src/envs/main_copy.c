
#include "main.h"

t_signal g_signal;

void	init_signal()
{
	g_signal.sigint = 0;
	g_signal.sigquit = 0;
	g_signal.exit_status = 0;
	g_signal.pid = 0;
}

void	sig_int()
{
	g_signal.exit_status = 1;
}

void	sig_quit()
{
	g_signal.exit_status = 1;
}

int	count_envp(char **envp)
{
	int count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

// char	**ft_split(char const *s, char c)
// int	ft_strncmp(const char *s1, const char *s2, size_t n)

int	free_node(t_envp **stack)
{
	t_envp	*head;
	t_envp	*tmp;

	head = *stack;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(stack);
	return (0);
}

// int	free_double_char(char **double_char)
// {
// 	char *p_double_char;

// 	if (double_char == NULL)
// 		return (0);
// 	p_double_char = *double_char;
// 	while (*p_double_char)
// 	{
// 		free(p_double_char);
// 		p_double_char++;
// 	}
// 	free(double_char);
// 	return (0);
// }



int	free_double_char(char **double_char)
{
    int i;
    int length;

	i = -1;
	length = count_double_char(double_char);
	while (++i < length)
        free(double_char[i]);
    free(double_char); 
}


// t_envp	*new_node(char **envp, int idx)
t_envp	*new_node(char **envp, int idx)
{
	t_envp	*first;
	char	**split_envp;

	first = (t_envp *)malloc(sizeof(t_envp));
	if (!first)
		return (NULL);
	split_envp = ft_split(envp[idx], '=');
	first->key = ft_strdup(split_envp[0]);
	if (!ft_strdup(split_envp[0], "PATH", 5))
	{
		//path는 구조체 안에 구조체..?
		first->value = ft_split(split_envp[1], ":");
	}
	else
		first->value = ft_strdup(split_envp[1]);
	first->next = 0;
	free_double_char(split_envp);
	return (first);
}


int	f_count_env(char **envp)
{
	int count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

void	f_init_env(char **envp, t_envp **n_envps)
{
	int		count;
	int		i;
	t_envp	*tmp;

	count = f_envp_count(envp);
	printf("var count : %d\n", count);
	*n_envps = new_node(envp, 0);
	tmp = *n_envps;
	i = 0;
	while (++i < count)
	{
		tmp->next = new_node(envp, i);
		tmp->count = count;
		tmp = tmp->next;
	}
	tmp->next = NULL;
}


//env 찾기 (1개) => echo 에서 사용할듯
	//
//

//f_init_env		// env 노드화 하기 

// f_unset_env() 	//삭제
// f_set_env()		//추가
// f_print_env()	//전체 출력



int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*input;
	t_envp	**n_envps;
	
	n_envps = NULL;
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	while ((input = readline("minishell > ")) && g_signal.exit_status)
	{
		init_signal();
		f_init_env(envp, n_envps);
		
		//parse_command(input);
		// if (input == NULL)
		// {

		// }
		// 빈입력
		add_history(input);
		parse_command(input);
		free(input);
	}
	
	return 0;
}
