#include "child_process.h"
#include "free.h"

//결과값 알아서
//builtin확인 및 어떤거 실행하는지 확인 함수
int	is_builtin(char *cmd_name)
{
    if (ft_strncmp(cmd_name, "cd", ft_strlen(cmd_name)) == 0)
        return (1);
    else if (ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name)) == 0)
        return (2);
    else if (ft_strncmp(cmd_name, "pwd", ft_strlen(cmd_name)) == 0)
        return (3);
	else if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name)) == 0)
        return (4);
	else if (ft_strncmp(cmd_name, "env", ft_strlen(cmd_name)) == 0)
        return (5);
    else if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name)) == 0)
        return (6);
    else if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name)) == 0)
        return (7);
    // printf("res %d\n", res);
    return (0);
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
		child->exe_path = find_exepath(child->cmd[0]);
		if (child->exe_path == NULL)
		{
			rdy = NULL;
			return (rdy);
		}
		child->state = STATE_EXEC_CMD;
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
	child->bulitin_code = 0;
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

int    execute_bulitin(t_child_process *child, t_minish *sh)
{
    int	res;
	// char	*cmd;
	// t_ready *rdy;
    // t_list *lst;
	
    // lst = sh->ready;
	// rdy = (t_ready *)(lst->content);
	// cmd = (char *)rdy->text->content;
    res = 0;
    if (child->bulitin_code == 1)
		res = f_cd(sh);
	else if (child->bulitin_code == 2)
        res = f_echo(sh);            
    else if (child->bulitin_code == 3)
        res = f_pwd(sh);            
    else if (child->bulitin_code == 4)
        res = f_export(sh);            
    else if (child->bulitin_code == 5)
        res = f_env(sh);            
    else if (child->bulitin_code == 6)
        res = 0; //f_unset
    else if (child->bulitin_code == 7)
        res = f_exit(sh);
	else
		printf("bc : %d\n", child->bulitin_code);
    
	child->state = STATE_COMPLETE;
    return (res);
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
			execute_bulitin(&child, sh);
			// printf("exec_bulitin(rdy, sh, &child)\n");
		else if (child.state == STATE_CHECK_PIPE)
			set_pipe(&child, sh, rdy);
		else if (child.state == STATE_EXEC_CMD)
			execute_cmd(&child);
	}
	
	child_process_handle(&child, rdy, sh);
	
	return (child.state);
}
