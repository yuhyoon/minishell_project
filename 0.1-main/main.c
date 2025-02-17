#include "parse_main.h"
# include "token_step-1_utils.h"
#include "token_step-1.c"
#include "token_step-2.c"

// cc -g main.c token_step-1_utils.c -lreadline libft/libft.a
int main() {
    char *input;
    char	*mask;
    t_list	*rdy_head;
    
    while (1) {
        input = readline("minishell> ");
        if (input == NULL) 
        {
            printf("\n입력이 널이면 종료\n");
            break;
        }
        if (ft_strlen(input) == 0) 
        {
            free(input);
            continue;
        }
        add_history(input);
        mask = generate_mask(input);
        rdy_head = parsing(input, mask, ft_strlen_delim(mask, '\n'));
	
	t_ready	*rdy;
	char	*txt;
	while (rdy_head)
	{
		rdy = (t_ready *)rdy_head->content;
		txt = (char *)(rdy->text->content);
		printf("%s\n", txt);
		rdy_head = rdy_head->next;
	}
		free(mask);
        free(input);
    }
    rl_clear_history();
    
    return 0;
}