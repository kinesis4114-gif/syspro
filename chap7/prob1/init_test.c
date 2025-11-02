#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "student.h"

int main() {
    struct student arr[] = {
        {1001001, "Jiwon", 100},
        {1001003, "jirong", 80},
        {1001006, "Mun", 95},
        {1001009, "BBo", 90}
    };

    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); exit(1); }

    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i) {
        if (write(fd, &arr[i], sizeof(arr[i])) != sizeof(arr[i])) {
            perror("write");
        }
    }

    close(fd);
    return 0;
}

