#include "main.h"
#include "parse.h"
#include "parse_step.h"
#include "stack.h"
#include "analysis.h"
#include "parse_utils.h"

void	set_char_state(char *s, t_char_state *char_state)
{
	char_state->quote = is_quote(*s);
	if (char_state->quote > 0)
		valid_quote(s, char_state->quote, char_state);
}

int	handle_putchar(t_char_state *char_state, int fd)
{
	int	size;

	size = 0;
	if (char_state->quote == 0)
	{
		size = putchar_quote_state_zero(char_state->current, fd);
	}	
	else
		size = read_store_fd(fd);
	return (size);
}

int write_replace_spaces(char *s, int replace_fd)
{
	t_char_state	char_state;
	int				i;
	int	len;
	
	init_char_state(&char_state, s);
	i = 0;
	while (*(char_state.current) != '\0')
	{
		set_char_state(char_state.current, &char_state);
		(char_state.current) += handle_putchar(&char_state, replace_fd);
	}
	if (*(char_state.current) == '\0')
	{	
		ft_putchar_fd('\n', replace_fd);
	}
	return (0);
}

char *generate_mask(t_ready *rdy)
{
	int	mask_fd;
	char	*mask;
	int	len;
	struct stat	st;

	mask_fd = open("mask_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write_replace_spaces(rdy->line, mask_fd);
	close(mask_fd);
	mask_fd = open("mask_fd", O_RDONLY);
	fstat(mask_fd, &st);
	len = (int)st.st_size;
	mask = malloc(sizeof(char) * len);
	read(mask_fd, mask, len);
	close(mask_fd);
	unlink("mask_fd");
	return (mask);
}
