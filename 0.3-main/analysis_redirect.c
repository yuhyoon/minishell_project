#include "analysis.h"

void	close_fd(int fd)
{
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
}

void    handle_heredoc_child(int write_fd, char *delimeter)
{
	char	*line;

	close_fd(write_fd - 1);
	printf("close : %d\n", write_fd - 1);
	printf("write_fd : %d\n", write_fd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			//> bash: warning: here-document at line ?? delimited by end-of-file (wanted `eof')
			write(write_fd, "\n", 1);
			break;
		}
		if (ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0)
		{
			if (line)
				free(line);
			break;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close_fd(write_fd);
	exitcode = 0;
	return ;
}

void    create_heredoc_pipe(int *read_fd, int *write_fd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	*read_fd = fd[0];
	*write_fd = fd[1];
}

void handle_heredoc_parent(t_redrct *rdrct, int read_fd, int write_fd, pid_t child_pid)
{
    int status;

    close_fd(write_fd);
    rdrct->fd = read_fd;
    if (waitpid(child_pid, &status, 0) == -1) 
        exit(EXIT_FAILURE);
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
    {
		// close_fd(read_fd);
        // rdrct->fd = -1;
		exit(EXIT_FAILURE);
    }
}

void	f_heredoc(t_redrct *rdrct)
{
	pid_t	pid;
	int		read_fd;
	int		write_fd;

	if (!rdrct->obj || ft_strlen(rdrct->obj) < 1)
	{
		write(2, "bash: syntax error near unexpected token `newline'\n", 51);
		return ;
	}
	create_heredoc_pipe(&read_fd, &write_fd);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		// printf("child\n");
		handle_heredoc_child(write_fd, rdrct->obj);
	}
	else
	{
		// printf("parent %d\n", pid);		
		handle_heredoc_parent(rdrct, read_fd, write_fd, pid);
	}
}

t_redrct	*init_rdrct(void)
{
	t_redrct	*rdrct;

	rdrct = malloc(sizeof(t_redrct));
	ft_memset(rdrct, 0, sizeof(rdrct));
	return (rdrct);
}

int create_rdrct(char *src, char *mask, t_list **head)
{
	int			i;
	t_redrct	*new;
	char		*str;
	int			len;
	t_list		*lst;

	lst = ft_lstnew(init_rdrct());
	i = 0;
	new = ((t_redrct *)((lst)->content));
	new->type = mask[i];
	while (mask[i] == new->type)
		i++;
	new->parts = i;
	while (mask[i] == NONE)
		i++;
	len = count_text(&mask[i]);
	ft_memset(&mask[i], new->type, len);
	str = malloc(sizeof(char) * (len + 1));
	ft_memcpy(str, &src[i], len);
	str[len] = '\0';
	new->obj = str; //리다이렉트 다 만든 상태
	//히어독일때 fd 갱신 처리
	if (new->parts == 2 && new->type == IN_RD)
		f_heredoc(new);
	ft_lstadd_back(head, lst);
	return (i + len);
}
