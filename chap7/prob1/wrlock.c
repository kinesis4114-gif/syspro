#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "student.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Usage: %s datafile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct student record;
    int target_id;

    printf("Enter StudentID you want to modify : ");
    if (scanf("%d", &target_id) != 1) {
        fprintf(stderr, "Invalid input\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    off_t offset = 0;
    int found = 0;
    while (1) {
        ssize_t r = pread(fd, &record, sizeof(record), offset);
        if (r == 0) break;         
        if (r < 0) { perror("pread"); break;}

        if (record.id == target_id) {
            found = 1;
            struct flock lock;
            lock.l_type = F_WRLCK;       
            lock.l_whence = SEEK_SET;
            lock.l_start = offset;        
            lock.l_len = sizeof(record); 

            if (fcntl(fd, F_SETLKW, &lock) == -1) {
                perror("fcntl - lock");
                close(fd);
                exit(EXIT_FAILURE);
            }

            printf("Name:%s\t StuID:%d\t Score:%d\n", record.name, record.id, record.score);
            printf("Enter new score: ");
            int newscore;
            if (scanf("%d", &newscore) != 1) {
                fprintf(stderr, "Invalid score\n");
                lock.l_type = F_UNLCK;
                if (fcntl(fd, F_SETLK, &lock) == -1) perror("fcntl - unlock");
                close(fd);
                exit(EXIT_FAILURE);
            }

            record.score = newscore;
            if (pwrite(fd, &record, sizeof(record), offset) != sizeof(record)) {
                perror("pwrite");
            }

            lock.l_type = F_UNLCK;
            if (fcntl(fd, F_SETLK, &lock) == -1) perror("fcntl - unlock");

            break;
        }
        offset += sizeof(record);
    }

    if (!found) {
        printf("No record %d\n", target_id);
    }

    close(fd);
    return 0;
}

