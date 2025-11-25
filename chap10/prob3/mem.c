#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[] = "Do you like Linux?";
    char *p;
    char *ptr;

    p = (char *)malloc(50);
    if (p == NULL) {
        printf("메모리 할당 오류\n");
        return 1;
    }

    memcpy(p, str, strlen(str) + 1);
    printf("%s\n", p);  

    memset(p + 12, 'l', 1);
    printf("%s\n", p);  

    ptr = (char *)memchr(p, 'l', strlen(p));
    printf("%s\n", ptr);

    memmove(p + 12, p + 7, 10);
    printf("%s\n", p); 

    free(p);
    return 0;
}

