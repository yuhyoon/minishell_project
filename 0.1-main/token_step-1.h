# include "parse_main.h"
# include "token_step-1_utils.h"

char 	*generate_mask(char *s);
int     write_replace_spaces(char *s, int replace_fd);
void	set_char_state(char *s, t_char_state *char_state);
int		handle_putchar(t_char_state *char_state, int fd);
int		putchar_quote_state_zero(char *current, int fd);
int		valid_quote(char *s, int quote, t_char_state *state);
void	store_quote_seq(t_char_state *char_state, int len, char *ss);
int		read_store_fd(int fd);