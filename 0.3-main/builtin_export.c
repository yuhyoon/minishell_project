/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:49:16 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/23 01:29:46 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
// #include "builtin.h"
int is_valid_name(char *name);
int is_valid_value(char *value, int index, t_minish *sh);

// export 정렬
void bubble_sort_envp(char **envp, int count)
{
	int i;
	int j;
	char *temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(envp[j], envp[j + 1], ft_strlen(envp[j])) > 0)
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// export node 생성
void f_sort_and_store_envp(char **envp, t_envp **sorted_envp)
{
	int count;
	int i;
	char **sorted_envp_array;

	count = f_count_char(envp);
	i = -1;
	sorted_envp_array = NULL;
	if (!envp || !sorted_envp)
	{
		ft_putstr_fd("Invalid Inputs", 2); // 지우기
		return;
	}
	sorted_envp_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!sorted_envp_array)
	{
		ft_putstr_fd("Failed allocated", 2); // 지우기
		return;
	}
	while (++i < count)
		sorted_envp_array[i] = ft_strdup(envp[i]);
	sorted_envp_array[i] = NULL;
	bubble_sort_envp(sorted_envp_array, count);
	f_init_env(sorted_envp_array, sorted_envp);
	free_double_char(sorted_envp_array);
}

void print_export(t_envp *lst)
{
	while (lst)
	{
		ft_putstr_fd("declare -x ", 2);
		ft_putstr_fd(lst->key, 2);
		if (lst->value)
		{
			ft_putstr_fd("=\"", 2);
			ft_putstr_fd(lst->value, 2);
			ft_putstr_fd("\"", 2);
		}
		ft_putstr_fd("\n", 2);
		lst = lst->next;
	}
}

void export_err_msg(char *cmds)
{
	int i;
	int size;

	i = -1;
	size = ft_strlen(cmds);
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd("`", 2);
	if (*cmds && cmds) // if (cmds && !(cmds[0] == '\0' && cmds[0] == ' '))
	{
		while (++i < size)
			write(2, &cmds[i], 1);
	}
	ft_putstr_fd("': ", 2);
	ft_putstr_fd("not a valid identifier\n", 2);
}

char	*get_name_in_value(char *value, int *i)
{
	char	*find_var;
	int		start;
	int		end;
	int		length;
	int		j;
	
	start = *i + 1;
	end = start;
	while (value[end] && value[end] != ' ' && value[end] != '\"')
		end++;
	length = end - start;
	find_var = (char *)malloc(sizeof(char) * (length + 1));
	if (!find_var)
		return (NULL);
	j = 0;
    while (j < length) 
	{
        find_var[j] = value[start + j];
        j++;
    }
	find_var[length] = '\0';
	return (find_var);
}

// int is_valid_value(char *value, int index, t_minish *sh)
// {
// 	int i;
// 	char *check_name;
// 	int quote_flags[2];
// 	int length;
// 	char *tmp; 

// 	i = index + 1;
// 	length = ft_strlen(value);
// 	quote_flags[0] = 0;
// 	quote_flags[1] = 0;
// 	while (i < length)
// 	{
// 		if (value[i] == '\'')
// 			quote_flags[0]++;
// 		if (value[i] == '\"')
// 			quote_flags[1]++;
// 		if (value[i] == '$')
// 		{
// 			check_name = get_name_in_value(value, &i);
//             if (!check_name) 
// 				return (-1);
//             tmp = find_get_t_envp(sh->n_export, check_name);
// 			free(check_name);
// 		}
// 		i++;
// 	}
// }

int is_valid_name(char *name)
{
	int valid;
	int flag;
	int i;

	i = 0;
	flag = 0;
	valid = ft_isalnum(name[0]);
	if (!(valid == 1 || valid == 2 || name[0] == '_'))
		return (-1);
	while (name[i])
	{
		if (name[i] == '=')
		{
			flag = 1;
			break;
		}
		i++;
	}
	if (flag == 1 && name[(i + 1)] != '\0') //key (0) / = (0) / value (0)
		return (2);
	if (flag == 0 && name[i] == '\0')
		return (0); // key (0) / = (x) / value (x)
	return (i);
}

int	is_valid_value2(char **cmd, size_t *index_stack, char *original_cmd, int is_name, t_minish *sh)
{
	int		length_original_cmds;
	char	*find_in_o_cmd;
	char	*new_cmd;
	int		tmp_i;
	int		index;

	length_original_cmds = ft_strlen(original_cmd);
	find_in_o_cmd = ft_strnstr(&(original_cmd[*index_stack]), *cmd, length_original_cmds);
	index = (find_in_o_cmd - original_cmd);
	(*index_stack) = index + 1;
	tmp_i = index + 2;
	if (is_name == 2 || is_name == 0)
		update_or_add_envp_node(&(sh->n_export), *cmd);
	else if (is_name == 1)
	{
		if (original_cmd[tmp_i] == ' ')
			update_or_add_envp_node(&(sh->n_export), *cmd);
		else
		{
			if (*(cmd + 1) == NULL)
				update_or_add_envp_node(&(sh->n_export), *cmd);
			else
			{
				new_cmd = ft_strjoin(*cmd, *(cmd + 1));
				update_or_add_envp_node(&(sh->n_export), new_cmd);
				free(new_cmd);
				return (2);
			}
		}
	}
	else if (is_name == -1)
	{
		export_err_msg(*cmd);
		return (-1);
	}
	return (0);
}

void	export_update_or_add(char *mask, char **cmds, char *original_cmd, t_minish *sh)
{
	int		length_original_cmds;
	int		is_name;
	int		is_value;
	size_t	index_stack = 7;

	char	**current_cmd = cmds;
	length_original_cmds = ft_strlen(original_cmd);
	current_cmd++;
	while (*current_cmd != NULL)
	{
		is_name = is_valid_name(*current_cmd);
		is_value = is_valid_value2(current_cmd, &index_stack, original_cmd, is_name, sh);
		current_cmd++;
	}
}


int f_export(t_minish *sh)
{
	int size;
	char **cmds;
	char *original_cmd;
	original_cmd = sh->src;
	cmds = ((t_ready *)sh->ready->content)->cmd;
	size = f_count_char(cmds);
	if (size == 1)
		print_export(sh->n_export);
	else if (size > 1)
		export_update_or_add(sh->mask, cmds, original_cmd, sh);
	exitcode = 0;
	return (0); // 정상 종료
}
