#include "parse_main.h"
#include "token_step-1_utils.c"

typedef struct s_ready
{
	t_list	*text;
	t_list	*io;
	t_list	*dolar;
	struct s_ready	*next;	
}t_ready;

typedef struct s_exe_info
{
	char	**cmd;
	int	in;
	int	out;
	struct s_exe_info	*next;
}t_exe_info;

typedef struct s_dollar
{
	char	pos;
	char	*str;
}t_dollar;


//return length
int	create_meta(char *src, char *mask, t_ready **rdy)
{
	int	i;
	t_list	*io;
	t_list	*dolar;

	init_ready();
	i = 0;
	if (mask[i] <= 1)
	{
		i++;	
	}
	else if (mask[i] == IN_RD || mask[i] == OUT_RD)
	{
		i += create_io(src, mask, rdy);
	}
	else if (mask[i] == DOLLAR)
	{
		i += create_dolar(src, mask, rdy);
	}
	return (i);
}

int	execute_meta(t_ready **rdy)
{
	while (is_empty((*rdy)->io) == false)
	{
		ft_lstclear(&(*rdy)->io, execute_rd());
	}
	while (is_empty((*rdy)->dolar) == false)
	{
		ft_lstclear(&(*rdy)->dolar, execute_rd());
	}
	
}

void *parsing(char *src, char *mask, int len)
{
	int		i;
	t_ready	*rdy;
	t_exe_info *exe_head;

	create_ready(&rdy);
	i = 0;
	while (i < len)
	{
		i += create_meta(src, mask, &rdy);
		if (mask[i] == PIPE)
		{
			execute_meta(&rdy);
			create_text(rdy, &exe_head, src, mask);
			create_exeinfo(rdy, &exe_head, src, mask);
			i++;
		}
	}
	if (exe_head == NULL)
	{
		execute_meta(&rdy);
		create_text(rdy, &exe_head, src, mask);
		create_exeinfo(rdy, &exe_head, src, mask);
	}
	return (rdy);
}

int main()
{

}
