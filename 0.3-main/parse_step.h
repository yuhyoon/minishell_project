#ifndef PARSE_STEP_H
# define PARSE_STEP_H

//parse step 1
char 	*generate_mask(t_minish *sh);
int 	write_replace_spaces(char *s, int replace_fd);
int		handle_putchar(t_char_state *char_state, int fd);
void	set_char_state(char *s, t_char_state *char_state);
char	*read_maskfd(int mask_fd, int *len);

//parse step 2
void 	*parsing(t_minish *sh, int len);
int		handle_pipe(t_minish *sh, t_ready *current_rdy, t_list **rdrct, int save);
t_list *init_parsing_structure(t_list **rdy_head);
void	*create_rdy();

#endif
