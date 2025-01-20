/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:39:08 by hyeyeom           #+#    #+#             */
/*   Updated: 2024/12/22 01:08:58 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* * * * * * * * * * * * * * * * * * * * * 
* exit with no options
* echo with option -n 
* cd with only a relative or absolute path
* pwd with no options
* export with no options
* unset with no options
* env with no options or arguments


echo : -n 옵션을 살려야 -nnnnnn = -n => 뒤에 한 글자라도 다르면 n으로 취급 안함
옵션 옵션 옵션 echo -n -n -n -n hello -n  이렇게 있으면 하나라도 arg만나면 텍스트로 출력
파싱부에서 환경변수를 해석해서 넘겨주는 식으로 -> 다를 수 있음 ! 
내가 envp 관리하면 PWD라는 키를 던져서 값으로 받을 수 있도로 따로 관리하면 좋다
export 를 구현하려면, pwd라는 키를 받았을 때, 해당 노드를 리턴을 받아야 return 노드 해야 내가 다른 value를 수정하거나 뽑아올 수 있으니 관련 함수를 만드는게 좋다
=> 환경 변수 해석이 잘됐는지 확인..!

exit ? Ctrl + C / Ctrl + d
exit long long int 범위까지 numeric으로 가능하고 그 이상은 exit 출력후 'numeric argument required'으로 프롬프트에 나옴
그 이후에 $?을 프린트 하면 2가 출력됌
hyeyeom@c2r7s8:~$ bash
hyeyeom@c2r7s8:~$ exit a
exit
bash: exit: a: numeric argument required
hyeyeom@c2r7s8:~$ echo $?
2
hyeyeom@c2r7s8:~$ bash
hyeyeom@c2r7s8:~$ exit 1 1
exit
bash: exit: too many arguments
hyeyeom@c2r7s8:~$ exit
exit
hyeyeom@c2r7s8:~$ 

valgrind 해서 free 다 한지 체크해줘야함
-> 구조체 제대로 다 free 하고 이건 실행하다가 중간에도 가능하니까

cd - chdir 그냥 그대로 사용하면 됌 !
1. cd ~
unset HOME
cd -
=> OLDPWD로 가는 입력 방법

2. 그냥 cd
cd 
=> 결과 : HOME path로 가야함

3. pwd vs. oldpwd 
=>계속 업데이트 해줘야함

==> bash 실행하면서 $PWD $HOME $OLDPWD 진행하면서 이거 계속 확인하기..!


* pwd - getcwd
걍 이거 해주면됌 !
unset PWD 해도 getcwd(환경변수랑 상관없음)로 정확한 경로를 뱉어내야함..

* unset 
t_envp 해당 key 값을 가진 노드를 뱉어내는 함수를 만들면,
편하게 할 수 있다. 
free전 노드 삭제가 가능하도록
1. unset PWD OLDPWD HOME
unset 뒤에 오는 arg 모두 unset 됌 

2. unset /존재하지 않는 키/
이렇게 하면 아무런 동작 없이 프롬프트 반환

3. unset /존재하지 않는 키/ /존재하는 키/
존재하는 키는 unset 되어야함

==> 환경 변수 관리만 잘 해두면 됌

* export 
경우의 수가 여러가지.. 
1. export key=value
key의 값을 가진 노드가 있으면 변경 !
없으면 새로운 노드 생김 (+노드 새로 이어 붙이기)

2. export key=
빈 값으로 만들고 ="" (export)
env에서 grep으로 검색시 나옴 (env)

3. export key
빈 값으로 만들고 =은 없음(export)
env에서 grep으로 검색시 나오지 않음 (env)

4. export key+=value
존재하면 이어붙이고
없으면 새로 만들고

5.export
declare -x 붙어야함

6. key값이 유효한지 검사 (변수 만드는 규칙처럼 .. 확인해보기)
hyeyeom@c2r7s8:/home/hyeyeom$ export 42jdsklfjasl
bash: export: `42jdsklfjasl': not a valid identifier
hyeyeom@c2r7s8:/home/hyeyeom$ export =hello
bash: export: `=hello': not a valid identifier
hyeyeom@c2r7s8:/home/hyeyeom$ export ^hello
bash: export: `^hello': not a valid identifier
hyeyeom@c2r7s8:/home/hyeyeom$ export qwerqwqw@eare=asdlfkj
bash: export: `qwerqwqw@eare=asdlfkj': not a valid identifier

=> export에서 구조체 seg 뜨는 경우 많으니 넣기 전에 확인 제대로 하기

* env 
구조체로 만들어둔거 출력
출력문 while로 뽑아내는거 ft_printf

** 빌트인의 arg를 통일하는게 나중에 다른 함수 처리하는데 편하다
-> int	builtin_*(char **argv, 다른 구조체 필요하면..)
	==> 빌트인 함수들이 exit_status 반환하게 처리 

echo $? (exit_status를 보는 방법) => 정리한거 찾아서 넣어놓기 bash에서 실행해서 값 맞는지 확인
exit_status가 정상종료는 0 
exit_status가 1일때 정상종료 아님 !
echo $? + $?

execve의 return 값

* * * * * * * * * * * * * * * * * * * * * */

int	command_echo()
{

	return (0);
}

int command_cd()
{
	return (0);
}

int	command_pwd()
{

}

int	command_export()
{

}

int	command_unset()
{

}

int	command_env()
{

}

int	command_exit()
{

}

int	builtins_starter()
{
	// if ()
}
// bnf??