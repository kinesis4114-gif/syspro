#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_FILE "db.dat"
#define STRLEN 40

typedef struct {
    int  id;
    char bookname[STRLEN];
    char author[STRLEN];
    int  year;
    int  numofborrow;
    int  borrow;        // 0=False(대출가능), 1=True(대출중)
} Book;

int main(void) {
    FILE *fp = fopen(DB_FILE, "wb");
    if (!fp) {
        perror("db.dat 생성 실패");
        return 1;
    }

    int n;
    printf("-- bookcreate --\n");
    printf("등록할 책 개수: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("잘못된 개수입니다.\n");
        fclose(fp);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        Book b;
        printf("\n[%d번째 책] (id bookname author year numofborrow borrow)\n", i+1);
        printf("예) 1 1984 George 1949 7 0\n");
        if (scanf("%d %39s %39s %d %d %d",
                  &b.id, b.bookname, b.author, &b.year, &b.numofborrow, &b.borrow) != 6) {
            printf("입력 형식 오류\n");
            fclose(fp);
            return 1;
        }
        fwrite(&b, sizeof(Book), 1, fp);
    }

    fclose(fp);
    printf("\n=> %s 생성 완료\n", DB_FILE);
    return 0;
}

