/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:59:30 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/02/26 15:34:30 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include "../parse_main.h"

// #include <unistd.h>
// #include <stdio.h>

// unsigned int exitcode;

// int f_cwd(char **location)
// {
//     int res;
//     *location = getcwd(NULL, 0);
//     if (!location || !*location)
//         return (1);
//     return (0);
// }

// int f_pwd()
// {
//     int     res;
//     char    *location;
//     res = f_cwd(&location);
//     if (res)
//     {
//         exitcode = 1;
//         return (1);
//     }
//     printf("%s\n", location);
//     exitcode = 0;
//     return (0);
// }

// int main(int argc, char const *argv[])
// {
//     f_pwd();
//     return 0;
// }


int f_pwd(t_minish *sh)
{
    char *new_pwd;
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
    {
        exitcode = 1;
        return (1);
    }
    write(2, sh->pwd, ft_strlen(sh->pwd));
    write(2, "\n", 1);
    exitcode = 0;
    return (0);
}
