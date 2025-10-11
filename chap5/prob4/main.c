#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <fcntl.h>  
#include <sys/types.h>
#include <sys/stat.h> 

int main() {
    int fd1, fd2;
    const char *text1 = "Hello! Linux"; 
    const char *text2 = "Bye! Linux"; 
    
    mode_t file_mode = S_IRUSR | S_IWUSR; 

    fd1 = creat("myfile", file_mode);
    
    if (fd1 == -1) {
        perror("myfile");
        exit(1);
    }

    ssize_t len1 = write(fd1, text1, 12);
    if (len1 == -1) {
        perror("write error (text1)");
        close(fd1);
        exit(1);
    }

    fd2 = dup(fd1);
    if (fd2 == -1) {
        perror("dup error");
        close(fd1);
        exit(1);
    }
    
    ssize_t len2 = write(fd2, text2, 10);
    if (len2 == -1) {
        perror("write error (text2)");
        close(fd1);
        close(fd2);
        exit(1);
    }
    
    close(fd2);
    close(fd1);
    
    return 0;
}
