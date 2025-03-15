#ifndef BUILTIN_H
# define BUILTIN_H

# include "main.h"

//환경변수 관리용 구조체
typedef struct s_envp
{
	char	**o_envp; //원래 envp;
	int		count;
	char	*key;
	char	*value;
	struct s_envp	*next;
}				t_envp;

//확인용 함수 (지워주세요)
void	show_stack(t_envp *stack, char *str);

int		f_count_char(char **envp);
void	free_double_char(char **double_char);

t_envp	*new_node(char **envp, int idx);
void	f_init_env(char **envp, t_envp **n_envps);

void bubble_sort_envp(char **envp, int count);
// void	f_sort_and_store_envp(char *envp, t_envp **sorted_envp);
void f_sort_and_store_envp(char **envp, t_envp **sorted_envp);

// void	free_n_envps(t_envp **envp);
void	free_node_t_envp(t_envp **envp); //전이름 : free_n_envps
int	add_envp_node(t_envp **head, char *key, char *value);

int		update_envp_node(t_envp **head, char *key, char *value);
// void	update_or_add_envp_node(t_envp **head, char *key, char *value);
void	update_or_add_envp_node(t_envp **head, char *set);
void	delete_t_envp(t_envp **head, char *key); // void	delete_envp_node(t_envp **head, char *key);


#endif
