#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>.txt\n", argv[0]);
        exit(1);
    }

    const char *file_name = argv[1]; 
    int fd;
    
    mode_t file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 

    fd = open(file_name, O_RDWR | O_CREAT, file_mode); 

    if (fd == -1) {
        fprintf(stderr, "파일 열기 오류\n");
        exit(1);
    } else {
        printf("file %s success : %d\n", file_name, fd);
        
        if (close(fd) == -1) {
             perror("close error");
             exit(1);
        }
    }

    return 0;
}
