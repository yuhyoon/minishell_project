#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// Linked list node 구조체 (가정)
typedef struct s_node {
    char **cmd;
    struct s_node *next;
} t_node;

// main 생성시 불필요
// extern char **environ;

void execute_pipeline(t_node *head) {
    int fds[2][2];          // 고정 크기의 파이프 배열
    int pid;
    int first = 1;          // 첫 번째 명령어 플래그
    int status;

    while (head) {
        // 다음 파이프 생성
        if (head->next) {
            if (pipe(fds[1]) == -1) {
                printf("pipe error");
                exit(1);
            }
        }

        // 자식 프로세스 생성
        pid = fork();
        if (pid == -1) {
            printf("fork error");
            exit(2);
        }

        if (pid == 0) { // 자식 프로세스
            if (!first) {
                // 이전 파이프의 읽기 끝을 표준 입력에 연결
                dup2(fds[0][0], STDIN_FILENO);
                close(fds[0][0]);
                close(fds[0][1]);
            }

            if (head->next) {
                // 현재 파이프의 쓰기 끝을 표준 출력에 연결
                dup2(fds[1][1], STDOUT_FILENO);
                close(fds[1][0]);
                close(fds[1][1]);
            }

            // 명령어 실행 -> execve로 변경
            execvp(head->cmd[0], head->cmd);
            // execve(path, head->cmd, environ);
            printf("execvp error");
            exit(3);
        }

        // 부모 프로세스
        if (!first) {
            // 이전 파이프 닫기
            close(fds[0][0]);
            close(fds[0][1]);
        }

        // 현재 파이프를 다음 반복을 위해 이동
        if (head->next) {
            fds[0][0] = fds[1][0];
            fds[0][1] = fds[1][1];
        }
        first = 0; // 첫 번째 명령어 처리 완료
        head = head->next; // 다음 노드로 이동
    }

    // 모든 자식 프로세스 대기 -> waitpid로 변경
    while (wait(&status) > 0);
}

int main() {
    t_node cmd1 = { .cmd = (char *[]){"ls", NULL}, .next = NULL };
    t_node cmd2 = { .cmd = (char *[]){"grep", "main", NULL}, .next = NULL };
    t_node cmd3 = { .cmd = (char *[]){"sort", NULL}, .next = NULL };
    t_node cmd4 = { .cmd = (char *[]){"uniq", NULL}, .next = NULL };
    t_node cmd5 = { .cmd = (char *[]){"wc", "-l", NULL}, .next = NULL };

    cmd1.next = &cmd2;
    cmd2.next = &cmd3;
    cmd3.next = &cmd4;
    cmd4.next = &cmd5;

    execute_pipeline(&cmd1);
    return 0;
}
