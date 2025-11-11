#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define DB_FILE "db.dat"
#define STRLEN  40
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
static int stricmp_kor(const char *a, const char *b){ 
    for (;;a++,b++){
        int ca=tolower((unsigned char)*a);
        int cb=tolower((unsigned char)*b);
        if (ca!=cb) return ca-cb;
        if (ca==0)  return 0;
    }
}

int main(void){
    char key[STRLEN];
    printf("input name of book ) ");
    if (scanf("%39s", key)!=1){ puts("입력 오류"); return 1; }

    FILE *fp=fopen(DB_FILE,"rb");
    if(!fp){ perror("db.dat"); return 1; }

    Book b; int found=0;
    while (fread(&b,sizeof(Book),1,fp)==1){
        if (stricmp_kor(b.bookname, key)==0){
            found=1;
            print_header();
            print_one(&b);
            break;
        }
    }
    fclose(fp);

    if(!found){
        printf("not found book name : '%s'\n", key);
    }
    return 0;
}

