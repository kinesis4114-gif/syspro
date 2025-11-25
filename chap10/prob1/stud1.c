#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int hakbun;
    char name[20];
} Student;

int main() {
    int n;

    printf("몇 명의 학생을 입력하겠습니까? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    Student *stu = (Student *)malloc(sizeof(Student) * n);
    if (stu == NULL) {
        printf("메모리 할당 오류\n");
        return 1;
    }

    printf("%d 명의 학번과 이름을 입력하세요.\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d %s", &stu[i].hakbun, stu[i].name);
    }

    printf("\n* 학생 정보(역순) *\n");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d %s\n", stu[i].hakbun, stu[i].name);
    }

    free(stu);
    return 0;
}

