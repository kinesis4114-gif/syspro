#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char *argv[]) {
    FILE *fp;
    student s;
    int input_count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "w");

    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s' for writing.\n", argv[1]);
        perror("fopen");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "학번 이름 점수\n");
    while (1) {
        input_count = scanf("%d %s %hd", &s.id, s.name, &s.score);
        
        if (input_count == EOF) {
            break;
        }

        if (input_count != 3) {
            fprintf(stderr, "Warning: Please enter 3 fields (ID, Name, Score).\n");
            while (getchar() != '\n');
            continue; 
        }
        fprintf(fp, "%d %s %hd\n", s.id, s.name, s.score); 
    }

    fclose(fp);
    return 0;
}
