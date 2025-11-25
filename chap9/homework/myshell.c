#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024
#define MAX_ARGS 128

void trim(char *s) {
    char *p = s;
    while (*p == ' ' || *p == '\t') p++;
    if (p != s) memmove(s, p, strlen(p) + 1);
    int len = strlen(s);
    while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n'))
        s[--len] = '\0';
}

void run_command(char *cmdline) {
    char *argv[MAX_ARGS];
    char *infile = NULL;
    char *outfile = NULL;
    int background = 0;
    int argc = 0;
    int i;

    trim(cmdline);
    if (cmdline[0] == '\0')
        return;

    i = strlen(cmdline) - 1;
    while (i >= 0 && (cmdline[i] == ' ' || cmdline[i] == '\t'))
        i--;
    if (i >= 0 && cmdline[i] == '&') {
        background = 1;
        cmdline[i] = '\0';
    }

    trim(cmdline);
    if (cmdline[0] == '\0')
        return;

    char *token = strtok(cmdline, " \t");
    while (token != NULL && argc < MAX_ARGS - 1) {
        if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t");
            if (token)
                outfile = token;
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t");
            if (token)
                infile = token;
        } else {
            argv[argc++] = token;
        }
        token = strtok(NULL, " \t");
    }
    argv[argc] = NULL;

    if (argc == 0)
        return;

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        if (infile) {
            int fd = open(infile, O_RDONLY);
            if (fd < 0) {
                perror("open input");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (outfile) {
            int fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0666);
            if (fd < 0) {
                perror("open output");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    } else {
        if (!background) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            printf("[bg] pid=%d\n", pid);
        }
    }
}

int main() {
    char line[MAX_LINE];

    while (1) {
        printf("shell> ");
        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        char *saveptr;
        char *cmd = strtok_r(line, ";", &saveptr);
        while (cmd != NULL) {
            run_command(cmd);
            cmd = strtok_r(NULL, ";", &saveptr);
        }
    }
    printf("\n");
    return 0;
}

