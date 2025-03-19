#ifndef CHILD_PROCESS_H
# define CHILD_PROCESS_H

# include "main.h"
# include "execution.h"
# include "error.h"

typedef enum s_child_state
{
	STATE_CHECK_RDRCT = 1,
	STATE_EXEC_BUILTIN,
	STATE_CHECK_CMD = 127,
	STATE_CHECK_PIPE,
	STATE_EXEC_CMD,
	STATE_COMPLETE
}t_child_state;

typedef struct s_child_process
{
	int				num;
	t_child_state	state;
	int				*pp;
	char			**cmd;
	char			*exe_path;
	int				input_fd;
	int				output_fd;
}t_child_process;

int	child_process(t_ready *rdy, int *pp, t_minish *sh);
void	execute_cmd(t_child_process *child);
void	set_pipe(t_child_process *child, t_minish *sh, t_ready *rdy);
void	*valid_redirect(t_child_process *child, t_ready *rdy);
int	prmssn_rdrct(t_redrct *rdrct);
void	init_child_process(t_child_process *child, int *pp, t_ready *rdy, t_minish *sh);
void	*valid_exepath(t_child_process *child, t_ready *rdy, t_minish *sh);
void    child_process_handle(t_child_process *child, t_ready *rdy, t_minish *sh);
void	close_pp(t_child_process *child, t_minish *sh);
bool	is_builtin(char *cmd_name);




#endif
