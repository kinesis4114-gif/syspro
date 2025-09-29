#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAX_LINES 5
#define MAX_LEN 100

int main() {
    char lines[MAX_LINES][MAX_LEN];
    int lengths[MAX_LINES];
    int i, j;
    
    printf("문자열 5개 입력:\n");

    for (i = 0; i < MAX_LINES; i++) {
        printf("> ");
        if (fgets(lines[i], MAX_LEN, stdin) == NULL) {
            break; 
        }
        lines[i][strcspn(lines[i], "\n")] = 0; 
        
        lengths[i] = strlen(lines[i]);
    }

    for (i = 0; i < MAX_LINES - 1; i++) {
        for (j = 0; j < MAX_LINES - 1 - i; j++) {
            if (lengths[j] < lengths[j+1]) {
                int temp_len = lengths[j];
                lengths[j] = lengths[j+1];
                lengths[j+1] = temp_len;

                char temp_line[MAX_LEN];
                copy(temp_line, lines[j]);
                copy(lines[j], lines[j+1]);
                copy(lines[j+1], temp_line);
            }
        }
    }

    printf("\n문자열 길이가 긴 순으로 정렬하여 출력:\n");
    for (i = 0; i < MAX_LINES; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}
