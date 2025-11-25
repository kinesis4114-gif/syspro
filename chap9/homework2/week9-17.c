#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARG 64
#define MAXLINE 256

void trim(char *s) {
    char *p = s;
    while (*p == ' ' || *p == '\t') p++;
    if (p != s) memmove(s, p, strlen(p) + 1);
    int len = strlen(s);
    while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == '\t'))
        s[--len] = '\0';
}

int main() {
    char line[MAXLINE];
    char *args[MAXARG];
    char *token, *saveptr;
    int background;
    int i, len;

    while (1) {
        printf("Pls input cmd : ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        line[strcspn(line, "\n")] = '\0';
        trim(line);
        if (line[0] == '\0')
            continue;

        if (strcmp(line, "exit") == 0)
            break;

        background = 0;
        len = strlen(line);
        if (len > 0 && line[len - 1] == '&') {
            background = 1;
            line[len - 1] = '\0';
            trim(line);
            if (line[0] == '\0')
                continue;
        }

        i = 0;
        token = strtok_r(line, " \t", &saveptr);
        while (token != NULL && i < MAXARG - 1) {
            args[i++] = token;
            token = strtok_r(NULL, " \t", &saveptr);
        }
        args[i] = NULL;
        if (i == 0)
            continue;

        printf("[%d] Parent process start\n", getpid());

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            printf("[%d] child process start\n", getpid());
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        } else {
            if (!background) {
                int status;
                pid_t child = waitpid(pid, &status, 0);
                printf("[%d] child process end %d\n", getpid(), child);
            }
            printf("SUCCESS\n");
        }
    }

    printf("Parent process end\n");
    printf("Exit\n");
    return 0;
}

