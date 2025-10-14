#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    long mode_long;
    mode_t newmode;

    if (argc != 3) {
        fprintf(stderr, "사용법: %s <8진수_권한> <파일_경로>\n", argv[0]);
        fprintf(stderr, "예시: %s 777 permission.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    mode_long = strtol(argv[1], (char **) NULL, 8);
    newmode = (mode_t)mode_long;

    if (chmod(argv[2], newmode) == -1) {
        perror(argv[2]);
        exit(1);
    }

    exit(0);
}
