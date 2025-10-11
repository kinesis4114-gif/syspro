#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#define MAX_LINES 10
#define MAX_CHARS_PER_LINE 100

char saveText[MAX_LINES][MAX_CHARS_PER_LINE];
int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[MAX_CHARS_PER_LINE];
    int total_lines = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <test_file.txt>\n", argv[0]);
        exit(1);
    }
    
    const char *filename = argv[1];

    if ((fp = fopen(filename, "r")) == NULL) {
        perror("File open error");
        exit(1);
    }
    while (fgets(buffer, MAX_CHARS_PER_LINE, fp) != NULL) {
        if (total_lines >= MAX_LINES) {
            fprintf(stderr, "Warning: Maximum line limit (%d) reached. Stopping read.\n", MAX_LINES);
            break;
        }
        strncpy(saveText[total_lines], buffer, MAX_CHARS_PER_LINE);
        total_lines++;
    }
    fclose(fp);
    for (int i = total_lines - 1; i >= 0; i--) {
        printf("%s", saveText[i]);
    }
    return 0;
}
