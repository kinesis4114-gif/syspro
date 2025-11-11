// bookupdate.c
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
    int  borrow; // 0=False, 1=True
} Book;

static void print_one(const Book *b) {
    printf("id  bookname            author           year  numofborrow  borrow\n");
    printf("%-3d %-18s %-15s %-5d %-12d %s\n",
           b->id, b->bookname, b->author, b->year, b->numofborrow,
           (b->borrow ? "True" : "False"));
}

int main(void) {
    printf("-- bookupdate --\n");
    printf("0 bookId: borrow book, 1 bookId: return book ) ");

    int op, key;
    if (scanf("%d %d", &op, &key) != 2 || (op != 0 && op != 1)) {
        printf("입력 형식: <op> <bookId>  (op: 0=borrow, 1=return)\n");
        return 1;
    }

    FILE *fp = fopen(DB_FILE, "rb+");
    if (!fp) { perror("db.dat 열기 실패"); return 1; }

    Book b;
    long pos;
    int found = 0;

    while ((pos = ftell(fp)), fread(&b, sizeof(Book), 1, fp) == 1) {
        if (b.id == key) {
            found = 1;
            if (op == 0) { // 대출
                if (b.borrow == 1) {
                    printf("You cannot borrow below book since it has been booked.\n");
                    print_one(&b);
                } else {
                    b.borrow = 1;
                    b.numofborrow += 1;
                    // 현재 레코드 위치로 되돌려 쓰기
                    fseek(fp, pos, SEEK_SET);
                    fwrite(&b, sizeof(Book), 1, fp);
                    fflush(fp);

                    printf("You've got bellow book..\n");
                    print_one(&b);
                }
            } else {        // 반납
                if (b.borrow == 0) {
                    printf("This book was not borrowed.\n");
                    print_one(&b);
                } else {
                    b.borrow = 0;
                    fseek(fp, pos, SEEK_SET);
                    fwrite(&b, sizeof(Book), 1, fp);
                    fflush(fp);

                    print_one(&b);
                }
            }
            break;
        }
    }

    if (!found) printf("해당 bookId(%d)를 찾을 수 없습니다.\n", key);

    fclose(fp);
    return 0;
}

