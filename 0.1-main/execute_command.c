#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// Linked list node 구조체
// typedef struct s_node {
//     char **cmd;
//     struct s_node *next;
// } t_node;

void execute_pipeline(t_node *head) 
{
    int fds[2][2];
    int pid;
    int first = 1;
    int status;

    while (head) 
    {
        if (head->next) {
            if (pipe(fds[1]) == -1) {
                printf("pipe error");
                exit(1);
            }
        }
        pid = fork();
        if (pid == -1) {
            printf("fork error");
            exit(2);
        }
        if (pid == 0) {
            if (!first) {
                dup2(fds[0][0], STDIN_FILENO);
                close(fds[0][0]);
                close(fds[0][1]);
            }
            if (head->next) {
                dup2(fds[1][1], STDOUT_FILENO);
                close(fds[1][0]);
                close(fds[1][1]);
            }

            execvp(head->cmd[0], head->cmd);
            // execve(path, head->cmd, environ);
            printf("execvp error");
            exit(3);
        }
        if (!first) {
            close(fds[0][0]);
            close(fds[0][1]);
        }
        if (head->next) {
            fds[0][0] = fds[1][0];
            fds[0][1] = fds[1][1];
        }
        first = 0;
        head = head->next;
    }
    while (wait(&status) > 0);
}
