#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct stat buf; 
    struct utimbuf time; 
    if (argc < 3) {
        fprintf(stderr, "How to use: %s file1 file2\n", argv[0]);
        exit(1);
    }
    if (stat(argv[1], &buf) < 0) {
        perror("stat()");
        exit(-1);
    }

    time.actime = buf.st_atime;
    time.modtime = buf.st_mtime;

    if (utime(argv[2], &time) < 0) {
        perror("utime()");
        exit(-1);
    } else {
        exit(0);
    }
}
