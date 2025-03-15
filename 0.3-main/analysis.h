#ifndef ANALYSIS_H
# define ANALYSIS_H

# include "parse.h"
# include "parse_utils.h"

//syntax
int			syntax_analysis(const char *m, int *len);
int			valid_meta(int token, char *mask);

//quote
int			valid_quote(char *s, int quote, t_char_state *state);
void		store_quote_seq(t_char_state *char_state, int len, char *ss);
int			putchar_quote_state_zero(char *current, int fd);
int			read_store_fd(int fd);

//redirect
t_redrct	*init_rdrct(void);
int 		create_rdrct(char *src, char *mask, t_list **head);

//dollar
void		create_text_list(t_ready *rdy, char *src, char *mask, t_minish *sh);
int			get_variable(char *mask, char *src, t_list **head);
int 		get_plain_text(char *s1, char *s2, char *src, t_list **head);
char		*valid_env(char *tmp);
int			count_text(char *mask);


//heredoc
void    close_fd(int fd);
void    handle_heredoc_child(int write_fd, char *delimeter);
void    create_heredoc_pipe(int *read_fd, int *write_fd);
void    handle_heredoc_parent(t_redrct *rdrct, int read_fd, int write_fd, pid_t pid);
void    f_heredoc(t_redrct *rdrct);

#endif
