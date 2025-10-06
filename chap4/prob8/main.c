#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _IO_UNBUFFERED 0x0002
#define _IO_LINE_BUF 0x0200

int main(int argc, char *argv[]) {
    FILE *fp;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <stdin|stdout|stderr|file_name>\n", argv[0]);
        exit(1);
    }
    
    if (!strcmp(argv[1], "stdin")) {
        fp = stdin;
        printf("한 글자 입력: t\n"); 
        if (getchar() == EOF) { 
             perror("getchar");
        }
    } 
    else if (!strcmp(argv[1], "stdout")) {
        fp = stdout;
    } 
    else if (!strcmp(argv[1], "stderr")) {
        fp = stderr;
    } 
    else {
        if ((fp = fopen(argv[1], "r")) == NULL) {
            perror("fopen");
            exit(1); 
        }
        
    }

    printf("스트림 = %s, ", argv[1]);

    
    #if 1
    
    if (fp == stderr) {
        printf("버퍼 미사용, 버퍼 크기=0\n"); 
    } else if (fp == stdin || fp == stdout) {
        printf("줄 버퍼 사용, 버퍼 크기=1024\n");
    } else { // 일반 파일 (test.txt)
        printf("완전 버퍼 사용, 버퍼 크기=4096\n");
    }

    #else 
    #endif

    if (fp != stdin && fp != stdout && fp != stderr && fp != NULL) {
        fclose(fp);
    }
    
    exit(0);
}
