#include <stdio.h>    
#include <stdlib.h>   
#include <unistd.h>   
#include <fcntl.h>    
#include <sys/types.h>
#include <sys/stat.h>

#include "student.h"

int main(int argc, char *argv[]) {
    int fd;
    Student record; 
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <record_file_name>.txt\n", argv[0]);
        exit(1);
    }
    
    const char *file_name = argv[1]; 
    mode_t file_mode = S_IRUSR | S_IWUSR | S_IRGRP;

    fd = open(file_name, O_WRONLY | O_CREAT, file_mode);
    
    if (fd == -1) {
        perror(file_name);
        exit(1);
    }
    printf("StuID\tName\tScore\n"); 
    fprintf(stdout, "Enter StuID, Name, Score (Ctrl+d to finish):\n");
    while (scanf("%ld %s %d", &record.stuID, record.name, &record.score) == 3) {
        printf("%ld\t%s\t%d\n", record.stuID, record.name, record.score);
        if (write(fd, &record, sizeof(Student)) == -1) {
            perror("write error");
            close(fd);
            exit(1);
        }
    }
    close(fd);
    return 0;
}
