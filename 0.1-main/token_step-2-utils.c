#include "parse_main.h"

void    *create_rdy(t_ready *head)
{
    t_ready *rdy;

    rdy = malloc(sizeof(t_ready));
    rdy->text = NULL;
    rdy->io = NULL;
    rdy->dolar = NULL;
    rdy->next = NULL;
    return (rdy);
}

int create_io(char *src, char *mask, int rd, t_ready **head)
{
    int i;
	t_redrct	*new;
	char	*str;
	int		len;

    i = 0;
    while (mask[i] == rd)
        i++;
    if (i >= 3)
    {
		//todo: error handling
    }
	new = malloc(sizeof(t_redrct));
	new->type = *mask;
	new->parts = i;
    while(mask[i] == 0)
		i++;
	len = ft_strlen(&mask[i]);
	ft_memset(&mask[i], rd, len);
	str = malloc(sizeof(char) * (len + 1));
	str = ft_memcpy(str, &src[i], len);
	str[len] = '\0';
	new->obj = str;
	return (i + len);
}

int	redirect_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}

int	here_doc(char *delim)
{
	char	*line;
	int		tmp_fd;
	int		len;

	tmp_fd = open(".tmp_heredoc", O_TMPFILE, 0600);
	while (1)
	{
		line = readline("> ");
		len = ft_strlen(line);
		if (!line || !ft_strncmp(line, delim, len));
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, len);
		write(tmp_fd, "\n", 1);
		free(line);
	}
	return (tmp_fd);
}

void execute_rd(t_ready *rdy)
{
	t_redrct	*rd;
	int	in;

	rd = rdy->io;
	if (rd->parts == 2)
		in = here_doc(rd->obj);
	else if (rd->parts == 1)
		in = redirect_in(rd->obj);
	if (in == -1)
	{
		//error
	}
	
}