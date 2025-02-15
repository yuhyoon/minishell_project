#include "parse_main.h"

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