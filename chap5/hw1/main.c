#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINES 10
#define MAX_CHARS_PER_LINE 100
char saveText[MAX_LINES][MAX_CHARS_PER_LINE];
int total_lines = 0;

int readFile(const char *filename) {
    FILE *fp;
    char buffer[MAX_CHARS_PER_LINE];
    total_lines = 0;

    if ((fp = fopen(filename, "r")) == NULL) {
        perror("File open error");
        return -1;
    }

    while (fgets(buffer, MAX_CHARS_PER_LINE, fp) != NULL) {
        if (total_lines >= MAX_LINES) {
            fprintf(stderr, "Warning: Maximum line limit (%d) reached. Remaining lines ignored.\n", MAX_LINES);
            break;
        }
        strncpy(saveText[total_lines], buffer, MAX_CHARS_PER_LINE - 1);
        saveText[total_lines][MAX_CHARS_PER_LINE - 1] = '\0';
        total_lines++;
    }
    fclose(fp);
    return total_lines;
}
void printLines(const char *input) {
    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < total_lines; i++) {
            printf("%s", saveText[i]);
        }
        return;
    }
    int start, end;
    if (sscanf(input, "%d-%d", &start, &end) == 2) {
        if (start < 1 || end > total_lines || start > end) {
            printf("Error: Invalid range.\n");
            return;
        }
        for (int i = start - 1; i < end; i++) {
            printf("%s", saveText[i]);
        }
        return;
    }
    char *token = strtok((char *)input, ",");
    while (token != NULL) {
        int line_num = atoi(token);

        if (line_num >= 1 && line_num <= total_lines) {
            printf("%s", saveText[line_num - 1]);
        } else {
        }
        token = strtok(NULL, ",");
    }
}
int main(int argc, char *argv[]) {
    char input_buffer[MAX_CHARS_PER_LINE];
    int lines_loaded;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <test_file.txt>\n", argv[0]);
        exit(1);
    }
    lines_loaded = readFile(argv[1]);
    if (lines_loaded == -1) {
        exit(1);
    }
    printf("File read success\n");
    printf("Total Line: %d\n", total_lines);
    printf("You can choose 1 ~ %d Line\n", total_lines);
    printf("Pls 'Enter' the line to select : ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        return 0;
    }
    input_buffer[strcspn(input_buffer, "\n")] = 0;
    printLines(input_buffer);
    return 0;
}
