#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char *argv[]) {
    struct student rec;
    FILE *fp;
    
    if (argc != 2) {
        fprintf(stderr, "How to use: %s FileName\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s' for reading.\n", argv[1]);
        perror("fopen");
        return 2;
    }
    
    fprintf(stdout, "학번 이름 점수\n");

    while (fscanf(fp, "%s %s %d", rec.id, rec.name, &rec.score) == 3) {

        fprintf(stdout, "%s %s %d\n", rec.id, rec.name, rec.score);
    }

    fclose(fp);
    
    return 0;
}
