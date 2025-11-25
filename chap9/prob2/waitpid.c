#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pid1, pid2, child, status;

    printf("[%d] parental process start\n", getpid());

    pid1 = fork();
    if (pid1 == 0) {
        printf("[%d] child process[1] start\n", getpid());
        usleep(1000);
        printf("[%d] child process[1] end\n", getpid());
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("[%d] child process[2] start\n", getpid());
        usleep(2000);
        printf("[%d] child process[2] end\n", getpid());
        exit(2);
    }

    child = wait(&status);
    printf("[%d] child process[%d] %d end\n", getpid(), (child==pid1?1:2), child);
    printf("    end code %d\n", status >> 8);

    child = wait(&status);
    printf("[%d] child process[%d] %d end\n", getpid(), (child==pid1?1:2), child);
    printf("    end code %d\n", status >> 8);

    return 0;
}

