#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("사용법: copy <옵션 0|1|2> <원본파일> <복사파일>\n");
        return 1;
    }

    int option = argv[1][0] - '0';
    FILE *src = fopen(argv[2], "r");
    FILE *dst = fopen(argv[3], "w");

    if (!src || !dst) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(src)) != EOF) {
        if (option == 1) ch = tolower(ch); // 대문자 → 소문자
        else if (option == 2) ch = toupper(ch); // 소문자 → 대문자
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);

    // 결과 확인용 출력
    dst = fopen(argv[3], "r");
    printf("결과 (%s 파일 내용): ", argv[3]);
    while ((ch = fgetc(dst)) != EOF) {
        putchar(ch);
    }
    printf("\n");
    fclose(dst);

    return 0;
}

