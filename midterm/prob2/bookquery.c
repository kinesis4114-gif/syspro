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

static void print_header(void) {
    printf("id  bookname            author           year  numofborrow  borrow\n");
}

static const char* b2s(int borrow) { return borrow ? "True" : "False"; }

int main(void) {
    printf("-- bookquery --\n");
    printf("( 0: list of all books, 1: list of available books ) ");
    int mode;
    if (scanf("%d", &mode) != 1 || (mode != 0 && mode != 1)) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    FILE *fp = fopen(DB_FILE, "rb");
    if (!fp) { perror("db.dat 열기 실패"); return 1; }

    Book b;
    if (mode == 0) {
        printf("\n0: list of all books\n");
        print_header();
        while (fread(&b, sizeof(Book), 1, fp) == 1) {
            printf("%-3d %-18s %-15s %-5d %-12d %s\n",
                   b.id, b.bookname, b.author, b.year, b.numofborrow, b2s(b.borrow));
        }
    } else {
        printf("\n1: list of available books\n");
        print_header();
        while (fread(&b, sizeof(Book), 1, fp) == 1) {
            if (b.borrow == 0) {
                printf("%-3d %-18s %-15s %-5d %-12d %s\n",
                       b.id, b.bookname, b.author, b.year, b.numofborrow, b2s(b.borrow));
            }
        }
    }
    fclose(fp);
    return 0;
}

