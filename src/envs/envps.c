// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#include "envp.h"

// typedef struct s_envp
// {
//     char    **o_envp; // 원래 envp;
//     int     count;
//     char    *key;
//     char    *value;
//     struct s_envp    *next;
// }               t_envp;

// size_t ft_strlen(const char *str)
// {
//     size_t i = 0;
//     while (str[i])
//         i++;
//     return i;
// }

// char    *ft_strdup(char *src)
// {
//     char    *new_src;
//     int     src_l;
//     int     i;

//     src_l = ft_strlen(src);
//     new_src = (char *)malloc(sizeof(char) * (src_l + 1));  // 수정된 부분
//     if (!new_src)
//         return (NULL);
//     i = 0;
//     while (src[i] != '\0')
//     {
//         new_src[i] = src[i];
//         i++;
//     }
//     new_src[i] = '\0';
//     return (new_src);
// }

int main(int argc, char **argv, char **envp)
{
    t_envp *n_envps;

    n_envps = (t_envp *)malloc(sizeof(t_envp));
    if (!n_envps)
        return 1;  // malloc 실패 처리

    n_envps->o_envp = envp;  // 원본 envp를 가리키는 것이라 따로 해제할 필요 없음.
    n_envps->count = 3;
    n_envps->key = ft_strdup("key");
    n_envps->value = ft_strdup("value");

    if (n_envps->key == NULL || n_envps->value == NULL)
    {
        free(n_envps->key);
        free(n_envps->value);
        free(n_envps);
        return 1;
    }

    free(n_envps->key);
    free(n_envps->value);
    free(n_envps);
    return 0;
}
