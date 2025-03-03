#ifndef DELETE_H
# define DELETE_H

#include "parse_main.h"
# include "token_step-1_utils.h"
#include "stack.h"

void	del_text(void *txt);
void	del_redrct(void *rd);
void	del_ready(void *ready);
void	del_stack(void *st);

#endif