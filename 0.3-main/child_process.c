
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
}

void	*valid_exepath(t_child_process *child, t_ready *rdy, t_minish *sh)
{
	if (is_builtin(child->cmd[0]) == true)
	{
		child->state = STATE_EXEC_BUILTIN;
		return (rdy);
	}
	child->exe_path = get_exepath(rdy);
	if (child->exe_path == NULL)
	{
		rdy = NULL;
		return (rdy);
	}
	if (sh->cmd_count > 1)
		child->state = STATE_CHECK_PIPE;
	else
		child->state = STATE_EXEC_CMD;
}

void	init_child_process(t_child_process *child, int *pp, t_ready *rdy, t_minish *sh)
{
	child->num = rdy->num;
	child->pp = pp;
	child->cmd = rdy->cmd;
	//child->cmd = NULL;
	child->input_fd = STDIN_FILENO;
	//if (sh->cmd_count > 1 && child->num < sh->cmd_count)
	// 	child->input_fd = sh->prev_for_pipe;
	child->output_fd = STDOUT_FILENO;
	child->exe_path = NULL;
	if (rdy->rdrct != NULL)
		child->state = STATE_CHECK_RDRCT;
	else
		child->state = STATE_CHECK_CMD;
}


void	redirect_input(t_child_process *child, t_ready *rdy)
{
		if (rdy->rdrct_in)
		{
			dup2(rdy->rdrct_in->fd, child->input_fd); //n copy to rdy->input;
			//child->input_fd = rdy->rdrct_in->fd;
			close(rdy->rdrct_in->fd);
		}
}

void	redirect_output(t_child_process *child, t_ready *rdy)
{
		if (rdy->rdrct_out)
		{
		      dup2(rdy->rdrct_out->fd, child->output_fd); //n copy to rdy->input;
		      //child->output_fd = rdy->rdrct_out->fd;
			  close(rdy->rdrct_out->fd);
		}
}

void	*valid_redirect(t_child_process *child, t_ready *rdy)
{
	if (valid_rdrct(rdy) != 0 || redirect(&(rdy->rdrct), rdy) != 0)
		rdy = NULL;
	else
	{
		redirect_input(child, rdy);
		redirect_output(child, rdy);
		child->state = STATE_CHECK_CMD;
	}
	return (rdy);
}

void	set_pipe(t_child_process *child, t_minish *sh, t_ready *rdy)
{
	//printf("[[[[[set_pipe\n");
	//printf("prev for pipe: %d, child num:%d\n", sh->prev_for_pipe, child->num);
	if (sh->prev_for_pipe != -1)
	{
		dup2(sh->prev_for_pipe, child->input_fd);
		close(sh->prev_for_pipe);
	}
	//redirect_input(child, rdy);
	//redirect_output(child, rdy);
	if (child->num < sh->cmd_count && sh->cmd_count > 1)
	{
		printf("{{{{{{{{{{{{child num:%d, dup2,\n", child->num);
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
	//printf("[[[[[child_process\n");
	while (rdy != NULL && child.state < STATE_COMPLETE)
	{
		if (child.state == STATE_CHECK_RDRCT)
			rdy = valid_redirect(&child, rdy);
		else if (child.state == STATE_CHECK_CMD)
			rdy = valid_exepath(&child, rdy, sh);
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
