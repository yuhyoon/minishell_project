#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "parse.h"

int		ft_strlen_delim(char *s, char delim);
void	init_char_state(t_char_state *state, char *s);
int 	is_whitespace(char c);
int		is_quote(char c);
int 	ft_ismeta(char *input);

#endif