#ifndef ANALYSIS_H
# define ANALYSIS_H

# include "parse.h"

//syntax
int			syntax_analysis(char *mask);
int			valid_meta(int token, char *mask);

//quote
int			valid_quote(char *s, int quote, t_char_state *state);
void		store_quote_seq(t_char_state *char_state, int len, char *ss);
int			putchar_quote_state_zero(char *current, int fd);

//redirect
t_redrct	*init_rdrct(void);
int 		create_rdrct(char *src, char *mask, t_list **head);

//dollar
void		create_text_list(t_ready *rdy, char *src, char *mask, t_minish *sh);
int			get_variable(char *mask, char *src, t_list **head);
int 		get_plain_text(char *s1, char *s2, char *src, t_list **head);
char		*valid_env(char *tmp);
int			count_text(char *mask);

#endif