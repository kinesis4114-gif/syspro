#include <stdio.h>
#include <stdlib.h>
#include "student.h" // student.h 헤더 파일 포함

int main(int argc, char *argv[]) {
    FILE *fp;
    student s;
    int input_count;

    // 5. 예외 처리: 명령줄 인수가 1개 입력되지 않은 경우 (총 2개여야 함)
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 파일 열기: 파일에 새로 작성하는 모드("w")로 엽니다.
    fp = fopen(argv[1], "w");

    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file '%s' for writing.\n", argv[1]);
        perror("fopen");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "학번 이름 점수\n");

    // 3. 학번, 이름, 점수를 입력받는 루프
    while (1) {
        // 표준 입력(stdin)에서 학번, 이름, 점수를 읽습니다.
        // 성공적으로 읽은 항목의 개수를 input_count에 저장합니다.
        input_count = scanf("%s %s %d", s.id, s.name, &s.score);

        // 입력 종료 (Ctrl+D 또는 파일 끝) 확인
        if (input_count == EOF) {
            break; // 입력 루프 종료
        }

        // 4. 정보 입력 시 학번, 이름, 점수를 모두 입력했는지 체크
        if (input_count != 3) {
            // 입력 누락 시 에러 메시지를 출력하고, 남은 입력 버퍼를 비웁니다.
            fprintf(stderr, "Warning: Please enter 학번, 이름, 점수.\n");
            while (getchar() != '\n'); // 버퍼 비우기
            continue; // 다음 입력으로 넘어갑니다.
        }

        // 2. 명령줄 인수로 받은 텍스트 파일에 입력받은 학생 정보를 저장 (fprintf 사용)
        fprintf(fp, "%s %s %d\n", s.id, s.name, s.score);
    }

    fclose(fp);
    return 0; 
}
