#include <stdio.h>   
#include <stdlib.h>   
#include <unistd.h>  
#include <fcntl.h>   
#include <sys/types.h>
#include <sys/stat.h>

#include "student.h" 
long stuID_to_record_index(long stuID) {
    return 0;
}

int main(int argc, char *argv[]) {
    int fd;
    long search_stuID;  
    char continue_flag; 
    Student record;     
    ssize_t bytes_read; 

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <record_file_name>.txt\n", argv[0]);
        exit(1);
    }
    
    const char *file_name = argv[1]; 
    
    fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror(file_name);
        exit(1);
    }
    
    do {
        printf("Enter StudentID to search:");
        if (scanf("%ld", &search_stuID) != 1) {
            while (getchar() != '\n'); 
            continue;
        }
        if (lseek(fd, 0, SEEK_SET) == -1) {
            perror("lseek error");
            close(fd);
            exit(1);
        }

        int found = 0;

        while ((bytes_read = read(fd, &record, sizeof(Student))) == sizeof(Student)) {
            if (record.stuID == search_stuID) {
                printf("Name:%s\tStuID:%ld\tScore:%d\n", record.name, record.stuID, record.score);
                found = 1;
                break; 
            }
        }
        if (!found) {
            if (search_stuID == 0) {
                 printf("레코드 0 없음\n");
            } else {
                 printf("Record %ld Null\n", search_stuID);
            }
        }
        printf("Continue? (Y/N)");
        scanf(" %c", &continue_flag); 

    } while (continue_flag == 'Y' || continue_flag == 'y');

    close(fd);
    return 0;
}
