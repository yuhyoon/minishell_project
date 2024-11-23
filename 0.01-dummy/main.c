
#include "main.h"

#define MAX_COMMAND_LENGTH 1024

/*
 *explain the pipex_quote()
 str_dup을 순회함. i만큼.
 1. If str_dup[i] is whitespace, change it to '\0'
 2. If str_dup[i]is quote, change it to '\0'. And subsequent quote to '\0' 
	(처음 찾은 쿼트를 널로 바꾸고 이후 나오는 쿼트도 널로 바꾼다)

* bug: 
 If small quote in double quote (e.g: "l's'")
 pipex_quote remove all quotes (e.g: ls)
 (더블 쿼트 안에 스몰쿼트나 스몰쿼트 안에 더블쿼트가 있거나 상관없이 쿼트들을 전부다 지워버림)
*/
int	pipex_quote(char *str_dup)
{
	int		len;
	int		i;

	len = ft_strlen(str_dup);
	i = 0;
	while (i < len && str_dup[i] != '\0')
	{
		if (ft_strspn(str_dup + i, "\'\""))
		{
			str_dup[i] = '\0';
			i++;
			i += ft_strcspn(str_dup + i, "\'\"");
			str_dup[i] = '\0';
		}
		if (str_dup[i] == ' ')
			str_dup[i] = '\0';
		i++;
	}
	return (i);
}

int	pipex_get_size(char *s, int len)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (i < len)
	{
		if (s[i] != '\0')
		{
			cnt++;
			while (i < len && s[i] != '\0')
				i++;
		}
		if (i >= len)
			break ;
		i++;
	}
	return (cnt);
}

char	**pipex_splited(char *s_dup, int w, char **abs)
{
	int		cnt;
	int		index_jump;

	cnt = 0;
	while (cnt < w)
	{
		while (*s_dup == '\0')
			s_dup++;
		abs[cnt] = ft_strdup(s_dup);
		index_jump = ft_strlen(abs[cnt]);
		s_dup = s_dup + index_jump;
		cnt++;
	}
	abs[cnt] = NULL;
	return (abs);
}

char	**pipex_split(char *s)
{
	int		s_len;
	char	*s_dup;
	int		w;
	char	**abs;

	s_len = ft_strlen(s);
	s_dup = ft_strdup(s);
	if (s_len < pipex_quote(s_dup))
	{
		free(s_dup);
		s_dup = NULL;
		return (NULL);
	}
	w = pipex_get_size(s_dup, s_len);
	abs = (char **)malloc(sizeof(char *) * (w + 1));
	if (!abs)
		return (0);
	pipex_splited(s_dup, w, abs);
	
	//이건 뭐하는거지..?
	for (int i; i < w; i++)
	{
		printf("%s\n", abs[i]);
	}
	return (abs);
}

int execute_single(char *single_command, char **argv, char **envp)
{
	int childPid;
	int status;

	childPid = fork();
	if (childPid == 0)
	{
		if (ft_strncmp("/bin/ls", single_command, ft_strlen(single_command)) || \
			ft_strncmp("ls", single_command, ft_strlen(single_command)))
			execve("/bin/ls", argv , envp);
	}
	else if (childPid > 0)
	{
		int waitPid;

		waitPid = wait(&status);
		if (waitPid == -1)
		{
			printf("에러넘버 : %d\n", errno);
			perror("wait 함수 오류 반환");
		}
		else
		{
			if (WIFEXITED(status))
				printf("wait : 자식 프로세스 정상 종료 %d\n",WEXITSTATUS(status));
			else if(WIFSIGNALED(status))
                printf("wait : 자식 프로세스 비정상 종료 %d\n",WTERMSIG(status));
		}
		printf("부모 종료 %d %d\n", waitPid, WTERMSIG(status));
	}
	else
	{
		perror("Fork Fail!");
		return (-1);
	}
	return (0);
}


void parse_command(char *cmd, char **argv, char **envp)
{
	char	**splited_cmd;
	char	*p_splited_cmd;
	int		count;

	splited_cmd = pipex_split(cmd);
	p_splited_cmd = *splited_cmd;
	while (*splited_cmd++)
		count++;

	//SINGLE COMMEND
	if (count == 1)
	{
		int res = execute_single(p_splited_cmd, argv, envp);
		printf("res : %d\n", res);
	}	
	//MULTIPLE COMMENDS
	if (count > 1)
	{

	}
	// hyeyeom_function(splited_cmd);	
}

// cc -g main.h.c -lreadline ./libft/libft.a -o dummy_1020
int main(int argc, char **argv, char **envp) {
    char *input;
    
	input = NULL;
	// 프롬프트를 표시하고 사용자 입력을 받습니다.
	(void)argc;
    while (input = readline("minishell> ")) 
	{
        //ctrl d 처럼 입력이 널값이면 종료
        if (input == NULL) {
            printf("\n입력이 널이면 종료\n");
            break;
        }
        
        // 빈 입력은 무시
        if (strlen(input) == 0) {
            free(input);
            continue;
        }
        
		
        // 입력을 히스토리에 추가
        add_history(input);
        
        // 명령어를 파싱
        parse_command(input, argv, envp);
        
        // 입력 메모리를 해제
        free(input);
    }
    
    // 프로그램 종료 시 히스토리를 정리
    rl_clear_history();
    
    return 0;
}
