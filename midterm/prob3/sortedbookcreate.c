#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_FILE "db.dat"
#define STRLEN  40
#define MAXN    400

typedef struct {
    int  id; char bookname[STRLEN]; char author[STRLEN];
    int  year; int numofborrow; int borrow;
} Book;

static int cmp_year_desc(const void *a, const void *b){
    const Book *x=a, *y=b;
    if (y->year != x->year) return y->year - x->year;
    return x->id - y->id;
}

int main(void){
    int n;
    printf("-- bookcreate(sorted by year desc) --\n");
    printf("등록할 책 개수: ");
    if (scanf("%d",&n)!=1 || n<=0 || n>MAXN){ puts("잘못된 개수"); return 1; }

    Book arr[MAXN];
    printf("(입력 형식) id bookname author year numofborrow borrow\n");
    for (int i=0;i<n;i++){
        if (scanf("%d %39s %39s %d %d %d",
                  &arr[i].id, arr[i].bookname, arr[i].author,
                  &arr[i].year, &arr[i].numofborrow, &arr[i].borrow) != 6){
            puts("입력 형식 오류"); return 1;
        }
    }

    qsort(arr, n, sizeof(Book), cmp_year_desc);

    FILE *fp=fopen(DB_FILE,"wb");
    if(!fp){ perror("db.dat"); return 1; }
    fwrite(arr, sizeof(Book), n, fp);
    fclose(fp);

    puts("=> db.dat 저장 완료(출판년도 내림차순).");
    return 0;
}

