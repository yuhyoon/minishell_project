
#include "child_process.h"
#include "free.h"



bool	is_builtin(char *cmd_name)
{
	return (false);
}

void	close_pp(t_child_process *child, t_minish *sh)
{
	if (child->num < sh->cmd_count)
	{
		close(child->pp[0]);
		close(child->pp[1]);
	}
}
void    child_process_handle(t_child_process *child, t_ready *rdy, t_minish *sh)
{
	if (child->state == STATE_CHECK_RDRCT || child->state == STATE_CHECK_PIPE)
		close_pp(child, sh);
	else if (child->state == STATE_CHECK_CMD)
		err_exec(127, child->cmd[0]);
	child->state = 0;
}

void	*valid_exepath(t_child_process *child, t_ready *rdy)
{
	child->cmd = create_str_2(&rdy->text);
//	char *hmm[] = {"q"};
//	child->cmd = hmm;
	if (is_builtin(child->cmd[0]) == true)
	{
		child->state = STATE_EXEC_BUILTIN;
		return (rdy);
	}
	child->exe_path = find_exepath(child->cmd[0]);
	if (child->exe_path == NULL)
	{
		rdy = NULL;
		return (rdy);
	}
	child->state = STATE_EXEC_CMD;
}

void	init_child_process(t_child_process *child, int *pp, t_ready *rdy, t_minish *sh)
{
	child->num = rdy->num;
	child->pp = pp;
	//child->cmd = rdy->cmd;
	child->cmd = NULL;
	child->input_fd = STDIN_FILENO;
	if (sh->cmd_count > 1 && child->num < sh->cmd_count)
	 	child->input_fd = sh->prev_for_pipe;
	child->output_fd = STDOUT_FILENO;
	child->exe_path = NULL;
	if (rdy->rdrct != NULL)
		child->state = STATE_CHECK_RDRCT;
	else
		child->state = STATE_CHECK_CMD;
}

void	*valid_redirect(t_child_process *child, t_ready *rdy)
{
	if (valid_rdrct(rdy) != 0 || redirect(&(rdy->rdrct), rdy) != 0)
		rdy = NULL;
	else
	{
		child->state = STATE_CHECK_CMD;
	}
	return (rdy);
}

void	set_pipe(t_child_process *child, t_minish *sh, t_ready *rdy)
{
	if (sh->prev_for_pipe != -1)
	{
		dup2(sh->prev_for_pipe, child->input_fd);
		close(sh->prev_for_pipe);
	}
	if (child->num < sh->cmd_count && sh->cmd_count > 1)
	{
		dup2(child->pp[1], child->output_fd);
		close(child->pp[1]);
		close(child->pp[0]);
	}
	child->state = STATE_EXEC_CMD;
}

void	execute_cmd(t_child_process *child)
{
	if (execve(child->exe_path, &child->cmd[0], NULL) != -1)
		child->state = STATE_COMPLETE;
}

int	child_process(t_ready *rdy, int *pp, t_minish *sh)
{
	t_child_process	child;

	init_child_process(&child, pp, rdy, sh);

	while (rdy != NULL && child.state < STATE_COMPLETE)
	{
		if (child.state == STATE_CHECK_RDRCT)
			valid_redirect(&child, rdy);
		else if (child.state == STATE_CHECK_CMD)
			rdy = valid_exepath(&child, rdy);
		else if (child.state == STATE_EXEC_BUILTIN)
			printf("exec_bulitin(rdy, sh, &child)\n");
		else if (child.state == STATE_CHECK_PIPE)
			set_pipe(&child, sh, rdy);
		else if (child.state == STATE_EXEC_CMD)
			execute_cmd(&child);
	}
	
	child_process_handle(&child, rdy, sh);
	
	return (child.state);
}
