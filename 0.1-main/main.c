#include "parse_main.h"
#include "token_step-1.c"

// cc -g dummy_main.c -lreadline libft/libft.a
int main() {
    char *input;
    char	*mask;
    
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
        parsing(input, mask, ft_strlen_delim(mask, '\n'));
		free(mask);
        free(input);
    }
    rl_clear_history();
    
    return 0;
}
