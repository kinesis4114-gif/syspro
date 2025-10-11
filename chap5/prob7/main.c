#include <stdio.h>  
#include <stdlib.h>   
#include <unistd.h>  
#include <fcntl.h>   
#include <sys/types.h>
#include <sys/stat.h>
#include "student.h" 

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
    fd = open(file_name, O_RDWR);
    if (fd == -1) {
        perror(file_name);
        exit(1);
    }
    do {
        printf("Enter StudentID to be modified: ");
        if (scanf("%ld", &search_stuID) != 1) {
            fprintf(stderr, "입력 오류\n");
            while (getchar() != '\n'); 
            continue;
        }
        if (lseek(fd, 0, SEEK_SET) == -1) {
            perror("lseek error");
            close(fd);
            exit(1);
        }

        int found = 0;
        long current_pos = 0;
        while ((bytes_read = read(fd, &record, sizeof(Student))) == sizeof(Student)) {
            current_pos = lseek(fd, 0, SEEK_CUR) - sizeof(Student); 
            if (record.stuID == search_stuID) {
                printf("StuID:%ld\tName:%s\tScore:%d\n", record.stuID, record.name, record.score);
                
                printf("New Score: ");
                if (scanf("%d", &record.score) != 1) {
                    fprintf(stderr, "점수 입력 오류\n");
                    while (getchar() != '\n');
                    found = 2;
                    break;
                }
                
                if (lseek(fd, current_pos, SEEK_SET) == -1) {
                    perror("lseek for write error");
                    close(fd);
                    exit(1);
                }

                if (write(fd, &record, sizeof(Student)) != sizeof(Student)) {
                    perror("write error");
                    close(fd);
                    exit(1);
                }
                
                found = 1;
                break;
            }
        }
        
        if (found == 0) {
            if (search_stuID == 0) {
                 printf("Record 0 Null\n");
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
