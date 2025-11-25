#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

// addq: tail에 새 노드 추가 (enqueue)
void addq(struct node **head, struct node **tail, int data) {
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;

    // 큐가 비어있을 경우 head와 tail 모두 newnode
    if (*tail == NULL) {
        *head = *tail = newnode;
    } else {
        (*tail)->next = newnode;
        *tail = newnode;
    }
}

// delete: head에서 제거 (dequeue)
int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        printf("Queue is empty!\n");
        return -1;
    }

    struct node *tmp = *head;
    int value = tmp->data;

    *head = tmp->next;

    // 큐가 비게 되면 tail도 NULL로 초기화
    if (*head == NULL)
        *tail = NULL;

    free(tmp);
    return value;
}

// 전체 큐 출력
void printQueue(struct node *head) {
    printf("Print queue\n");
    while (head != NULL) {
        printf("%d\n", head->data);
        head = head->next;
    }
}

// 메인 함수 (자연수 입력 → enqueue, 자연수 외 입력 → 전체 큐 출력)
int main() {
    struct node *head = NULL;
    struct node *tail = NULL;

    while (1) {
        double num;
        int ret = scanf("%lf", &num);

        // 숫자 아닌 값 입력됨 → scanf 실패
        if (ret != 1) {
            printQueue(head);
            break;
        }

        // 자연수 아닌 값 입력됨
        if (num <= 0 || (int)num != num) {
            printQueue(head);
            break;
        }

        // 정상 자연수 입력 → enqueue
        addq(&head, &tail, (int)num);
    }

    return 0;
}

