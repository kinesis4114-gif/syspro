#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("my process number: [%d]\n", getpid());
    printf("my parent process number: [%d]\n", getppid());
    return 0;
}

