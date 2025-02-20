// // #include <stdio.h>
// // #include "../lib/libft/inc/libft.h"

// // typedef struct s_env_node {
// //     int idx;
// //     char *context;
// //     struct s_env_node *next;
// // } t_env_node;

// // int	main(int argc, char const *argv[], char **envp)
// // {
// //     char **takeout_env;
// //     int i;
    
// //     i = 0;
// //     // takeout_env = NULL;
// // 	takeout_env = ft_split(*envp, ' ');
// //     // while (*envp)
// //     // {
// //     //     envp++;
// //     // }
// //     printf("%s %s\n", takeout_env[0], takeout_env[1]);
// // 	printf("%s %s\n", takeout_env[2], takeout_env[3]);
    
// //     return 0;
// // }


// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cd.c                                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/09 16:16:17 by hyeyeom           #+#    #+#             */
// /*   Updated: 2025/02/09 16:51:18 by hyeyeom          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// // #include ""

// // cd - chdir 그냥 그대로 사용하면 됌 !
// // 1. cd ~
// // unset HOME
// // cd -
// // => OLDPWD로 가는 입력 방법
// // 2. 그냥 cd
// // cd 
// // => 결과 : HOME path로 가야함
// // 3. pwd vs. oldpwd 
// // =>계속 업데이트 해줘야함
// // ==> bash 실행하면서 $PWD $HOME $OLDPWD 진행하면서 이거 계속 확인하기..!


// // extern char **environ;

// // int main(int argc, char *argv[])
// // {
// // 	char	**new_argv;
// // 	char	command[] = "ls";
// // 	int		idx;

// // 	new_argv = malloc(sizeof(char *) * argc + 1);
// // 	// 명령어를 ls로 변경
// // 	new_argv[0] = command;

// // 	// command line으로 넘어온 parameter를 그대로 사용
// // 	for (idx = 1 ; idx < argc ; ++idx)
// // 		new_argv[idx] = argv[idx];

// // 	// argc를 execve 파라미터에 전달할 수 없기 때문에 NULL을 끝으로 지정해우저야 함
// // 	new_argv[argc] = NULL;

// // 	if (execve("/bin/ls", new_argv, environ) == -1){
// // 		fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno));
// // 		return 1;
// // 	}
// // 	printf("이후 로직은 실행되지 않습니다..\n");
// // 	return (0);
// // }

// #include <unistd.h>
// #include <string.h>

// //error

// //print_path

// //print_homepath

// char	*ft_getenv(char **envp)
// {
// 	char	*env;
// 	int		i;

// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		if (ft_strnstr(envp[i], "PATH=", 5))
// 			break ;
// 		i++;
// 	}
// 	env = envp[i];
// 	return (env);
// }

// char	*full_path(char *envp, char **cmd)
// {
// 	char	**d_envp;
// 	int		i;
// 	char	*cmd_path;
// 	char	*full_path;

// 	if (cmd == NULL)
// 		return (NULL);
// 	d_envp = ft_split(envp, ':');
// 	i = 0;
// 	cmd_path = ft_strjoin("/", cmd[0]);
// 	while (d_envp[i] != NULL)
// 	{
// 		full_path = ft_strjoin(d_envp[i], cmd_path);
// 		if (access(full_path, X_OK) == 0)
// 			break ;
// 		free(full_path);
// 		full_path = NULL;
// 		i++;
// 	}
// 	free_splited(d_envp);
// 	free(cmd_path);
// 	cmd_path = NULL;
// 	return (full_path);
// }

// // void	error_exit_cmd(char **cmd, char *f_p, t_fds *fds)
// // {
// // 	close_free(fds);
// // 	if (cmd == NULL && f_p == NULL)
// // 		error_exit("command error: pipex can excute shell command only");
// // 	free_splited(cmd);
// // 	free(f_p);
// // 	error_exit_errno("command error");
// // }


// int	cd_go_home(char **envp)
// {

// 	return (0);
// }


// int ft_cd(int argc, char **envp)
// {
// 	//현재 위치에서 적절한 파일이나 폴더 값인지 확인
// 	char    **new_argv;
// 	char	*p_env;
// 	char	**cmd;
// 	char	*f_p;

// 	// if (argc != 2)
// 	// 	return (0);

// 	p_env = ft_getenv(envp);
// 	// printf("%")
// 	// new_argv[argc] = NULL;

// 	// if (execve("bin/cd", new_argv, envp) == -1)
// 	// {
// 	// 	printf("bash: cd: %s : No such file or directory\n",  new_argv[1]);
// 	// 	return (1);
// 	// 	//적절하게 실행되지 않으니 Error 처리
// 	// }
// 	// if (f_p == NULL)
// 	// {
// 	// 	//error
// 	// }


	
// 	return (0);
// }

// int main(int argc, char const *argv[], char **envp)
// {
// 	ft_cd(argc, envp);
// 	return 0;
// }


#include <stdio.h>
#include "../../lib/libft/inc/libft.h"

char	*ft_getenv(char **envp)
{
	char	*env;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	env = envp[i];
	return (env);
}

char	*full_path(char *envp)
{
	int		i;
	// char	*cmd_path;
	char	**d_envp;
	char	*full_path;

	i = 0;
	d_envp = ft_split(envp, ':');
	// cmd_path = ft_strjoin("/", "cd");
	while (d_envp[i] != NULL)
	{
		full_path = ft_strjoin(d_envp[i], "/cd");
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (full_path);
}


// PATH=/opt/homebrew/bin:/Users/hyerimyeom/.nvm/versions/node/v22.11.0/bin:/Library/Frameworks/Python.framework/Versions/3.11/bin:/Library/Frameworks/Python.framework/Versions/3.7/bin:/Library/Frameworks/Python.framework/Versions/3.8/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/Python 3.7:/Applications/VMware Fusion.app/Contents/Public:/usr/local/share/dotnet:~/.dotnet/tools:/Library/Apple/usr/bin:/Users/hyerimyeom/.nvm/versions/node/v22.11.0/bin:/Library/Frameworks/Python.framework/Versions/3.11/bin:/Library/Frameworks/Python.framework/Versions/3.7/bin:/Library/Frameworks/Python.framework/Versions/3.8/bin:/Users/hyerimyeom/Library/Android/sdk/emulator:/Users/hyerimyeom/Library/Android/sdk/tools:/Users/hyerimyeom/Library/Android/sdk/tools/bin:/Users/hyerimyeom/Library/Android/sdk/platform-tools:/Users/hyerimyeom/.composer/vendor/bin:/Users/hyerimyeom/Library/Application Support/Code/User/globalStorage/github.copilot-chat/debugCommand:/Users/hyerimyeom/Library/Android/sdk/emulator:/Users/hyerimyeom/Library/Android/sdk/tools:/Users/hyerimyeom/Library/Android/sdk/tools/bin:/Users/hyerimyeom/Library/Android/sdk/platform-tools:/Users/hyerimyeom/.composer/vendor/binbash-3.2

int go_to_path(char *argv, char **envp)
{
	char	*p_env;
	char	*f_p;
	
	p_env = ft_getenv(envp);
	f_p = full_path(p_env);
	while (*f_p)
	{
		printf("%s\n", f_p);
		f_p++;
	}
	return (0);
}


int	f_cd()
{


}

int main(int argc, char *argv[], char **envp)
{
	f_cd();
	// /* code */
	// if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
	// 	return (0);
	// if (go_to_path(argv[1], envp))
		

	return 0;
}
