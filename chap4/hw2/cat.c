#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int file_copy(const char *file_path, int number_lines) {
    FILE *fp;
    int c;
    int line_number = 1;
    int newline_flag = 1; 

    fp = fopen(file_path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s'.\n", file_path);
        perror("fopen");
        return 0;
    }

    if (number_lines) {
        printf("%d ", line_number++);
        newline_flag = 0;
    } else {
        newline_flag = 0; 
    }

    while ((c = fgetc(fp)) != EOF) {
        putchar(c);

        if (c == '\n') {
            if (number_lines) {
                newline_flag = 1;
            }
        }
        
        if (newline_flag && number_lines) {
            printf("%d ", line_number++);
            newline_flag = 0;
        }
    }
    
    fclose(fp);
    return 1;
}

int main(int argc, char *argv[]) {
    int start_index = 1;
    int number_lines = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        number_lines = 1;
        start_index = 2;
    }
    if (start_index >= argc) {
        if (argc == 1) {
            file_copy("/dev/stdin", 0);
            return 0;
        }

        fprintf(stderr, "Error: No file specified.\n");
        return EXIT_FAILURE;
    }

    for (int i = start_index; i < argc; i++) {
        file_copy(argv[i], number_lines);
    }

    return 0;
}
