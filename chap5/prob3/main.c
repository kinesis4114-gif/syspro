#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 512

int main(int argc, char *argv[]) {
    int src_fd, dest_fd;
    char buffer[BUFSIZE];
    ssize_t bytes_read;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file>.txt <new_file>.txt\n", argv[0]);
        exit(1);
    }

    const char *src_file = argv[1]; 
    const char *dest_file = argv[2];
    
    src_fd = open(src_file, O_RDONLY);
    
    if (src_fd == -1) {
        perror(src_file);
        exit(1);
    }

    mode_t file_mode = S_IRUSR | S_IWUSR; 

    dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, file_mode);

    if (dest_fd == -1) {
        perror(dest_file);
        close(src_fd);
        exit(1);
    }
    
    while ((bytes_read = read(src_fd, buffer, BUFSIZE)) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("write error");
            close(src_fd);
            close(dest_fd);
            exit(1);
        }
    }

    if (bytes_read == -1) {
        perror("read error");
        exit(1);
    }

    if (close(src_fd) == -1) {
        perror("close source error");
        exit(1);
    }
    if (close(dest_fd) == -1) {
        perror("close destination error");
        exit(1);
    }
    
    return 0;
}
