#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct student {
    int id;
    char name[10];
    int score;
};

int main(int argc, char *argv[]) {
    int fd;
    struct student records[] = {
        {1001001, "Jiwon", 100},
        {1001003, "Jirong", 80},
        {1001006, "Mun", 95},
        {1001009, "BBo", 90},
        {1001010, "Kim", 75}
    };
    int num_records = sizeof(records) / sizeof(struct student);
    
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <filename>\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        perror("파일 생성 오류");
        exit(2);
    }

    if (write(fd, records, sizeof(struct student) * num_records) == -1) {
        perror("쓰기 오류");
        close(fd);
        exit(3);
    }
    
    printf("Successfully created %s with %d records.\n", argv[1], num_records);

    close(fd);
    return 0;
}
