/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyeyeom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:18:23 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/10/21 21:54:50 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dummy_main.h"

int	error_msg()
{
	perror("ERROR!");
}

void	hyeyeom_function(splited_cmd)
{
	
	// if ()
	// {
	// 	minishell_echo()
	// }
	// else if ()
	// {

	// }
	// else if ()
	// {
		
	// }
}

int	minishell_echo(char *str)
{
	// bash-5.2$       echo "hello"
	// echo 명령어가 나오기 전에 띄어쓰기가 엄청 많이 나와도 상관없음
	
	// 명령어 나누기
	// ft_split(str);
	// "echo -n" 이 맞는지 확인 
	// "echo" 도 맞는지 확인

	// "echo -n"이후 문자들을 얻어놓기
	printf("%s", str);
}

int	minishell_cd(char *str)
{
	// cd
	char *args = ft_split(str);
	// cd args가 하나인지 확인 
	// if (!ft_strcmp("cd", args[0]))	// 이건 앞에서 하겠네.. 
	// 	// return error_msg;
	if (ft_length(args) > 2) 		// 2개 
		// return error_msg;
	while (args[1])
	{
		
	}
}

int	minishell_pwd(char *str)
{
	// pwd는 명령어 외에 있으면 안됌
	// pwd: too many arguments

	// -L -P 외에는 없는 것으로 
	// pwd: bad option: -a

	// -L 옵션과 동일하게 작동
	if ()
	{
		
	}
	// man pwd 문서에서는 -P가 디폴트라고 나오지만
	// 실제 해보면 -L이 디폴트임 (관련서적이나 자료를 찾아보고 어떤 SHELL을 기준으로 할 것인지 설정)
	// ┌─(~/goinfre)─────────────────────────────────────────(hyeyeom@c2r11s3:pts/2)─┐
	// └─(00:52:20)──> pwd -P                                          ──(Fri,Oct18)─┘
	// /goinfre/hyeyeom
	// ┌─(~/goinfre)─────────────────────────────────────────(hyeyeom@c2r11s3:pts/2)─┐
	// └─(00:52:22)──> pwd -L                                          ──(Fri,Oct18)─┘
	// /home/hyeyeom/goinfre
	// ┌─(~/goinfre)─────────────────────────────────────────(hyeyeom@c2r11s3:pts/2)─┐
	// └─(00:52:24)──> pwd                                             ──(Fri,Oct18)─┘
	// /home/hyeyeom/goinfre
}