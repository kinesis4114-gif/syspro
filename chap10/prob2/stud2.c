#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node {
    int hakbun;
    char name[20];
    struct Node *next;
} Node;

int main() {
    Node *head = NULL; 
    Node *newNode;
    int hakbun;
    char name[20];
    int count = 0;

    printf("학번과 이름을 입력하세요\n");

    while (1) {
        if (scanf("%d", &hakbun) != 1) {
            break;
        }

        scanf("%s", name);

        newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("메모리 할당 오류\n");
            return 1;
        }

        newNode->hakbun = hakbun;
        strcpy(newNode->name, name);

        newNode->next = head;
        head = newNode;
        count++;
    }

    printf("\n* 학생 정보(역순) *\n");

    Node *p = head;
    while (p != NULL) {
        printf("학번: %d 이름: %s\n", p->hakbun, p->name);
        p = p->next;
    }

    printf("총 %d 명입니다.\n", count);

    p = head;
    while (p != NULL) {
        Node *tmp = p;
        p = p->next;
        free(tmp);
    }

    return 0;
}

