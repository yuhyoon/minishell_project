#ifndef CHILD_PROCESS_H
# define CHILD_PROCESS_H

# include "main.h"
# include "execution.h"
# include "error.h"

typedef enum s_child_state
{
	STATE_CHECK_RDRCT,
	STATE_EXEC_BUILTIN,
	STATE_CHECK_CMD,
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

#endif