#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFSIZE 512

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>.txt\n", argv[0]);
        exit(1);
    }

    const char *file_name = argv[1];
    int fd;
    char buffer[BUFSIZE];
    ssize_t bytes_read;
    
    long long total_size = 0; 
    
    fd = open(file_name, O_RDONLY);

    if (fd == -1) {
        perror(file_name);
        exit(1);
    }
    
    while ((bytes_read = read(fd, buffer, BUFSIZE)) > 0) {
        total_size += bytes_read;
    }
    
    if (bytes_read == -1) {
        perror("read error");
        close(fd);
        exit(1);
    }
    
    printf("%s File size : %lld Byte\n", file_name, total_size);

    if (close(fd) == -1) {
        perror("close error");
        exit(1);
    }

    return 0;
}
