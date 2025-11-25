#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = *top;
    *top = newnode;
}

int pop(struct node **top) {
    if (*top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    struct node *tmp = *top;
    int value = tmp->data;
    *top = tmp->next;
    free(tmp);
    return value;
}
void printStack(struct node *top) {
    printf("Print stack\n");
    while (top != NULL) {
        printf("%d\n", top->data);
        top = top->next;
    }
}

int main() {
    struct node *top = NULL;

    while (1) {
        double num;
        if (scanf("%lf", &num) != 1) break;
        if (num <= 0 || (int)num != num) {
            printStack(top);
            break;
        }

        push(&top, (int)num);
    }

    return 0;
}

