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

static const char* b2s(int b){ return b ? "True":"False"; }
static void print_header(void){
    printf("id  bookname            author           year  numofborrow  borrow\n");
}
static void print_one(const Book *p){
    printf("%-3d %-18s %-15s %-5d %-12d %s\n",
           p->id, p->bookname, p->author, p->year, p->numofborrow, b2s(p->borrow));
}
static int cmp_borrow_desc(const void *a, const void *b){
    const Book *x=a, *y=b;
    if (y->numofborrow != x->numofborrow) return y->numofborrow - x->numofborrow;
    return x->id - y->id;
}

int main(void){
    printf("-- bookquery --\n");
    printf("0: list of all books, 1: list of available books ) ");
    int mode; if (scanf("%d",&mode)!=1 || (mode!=0 && mode!=1)){ puts("잘못된 입력"); return 1;}

    FILE *fp=fopen(DB_FILE,"rb");
    if(!fp){ perror("db.dat"); return 1; }

    Book all[MAXN]; int m=0;
    while (m<MAXN && fread(&all[m], sizeof(Book), 1, fp)==1) m++;

    Book arr[MAXN]; int n=0;
    if (mode==0){
        memcpy(arr, all, sizeof(Book)*m); n=m;
        printf("\n0: list of all books\n");
    } else {
        for (int i=0;i<m;i++) if (all[i].borrow==0) arr[n++]=all[i];
        printf("\n1: list of available books\n");
    }

    qsort(arr, n, sizeof(Book), cmp_borrow_desc);
    print_header();
    for (int i=0;i<n;i++) print_one(&arr[i]);
    return 0;
}

