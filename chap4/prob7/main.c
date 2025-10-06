#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char *argv[]) {
    FILE *fp;
    student s;
    int read_count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s' for reading.\n", argv[1]);
        perror("fopen");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "학번 이름 점수\n");

    while (1) {
        read_count = fscanf(fp, "%d %s %hd", &s.id, s.name, &s.score);
        
        if (read_count == EOF || read_count != 3) {
            break; 
        }

        fprintf(stdout, "%d %s %hd\n", s.id, s.name, s.score);
    }

    fclose(fp);
    
    return 0;
}
