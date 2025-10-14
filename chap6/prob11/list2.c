#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <getopt.h> 
#define PATH_MAX 4096
int opt_i = 0; 
int opt_p = 0; 
int opt_Q = 0;
char type(mode_t mode) {
    if (S_ISREG(mode))
        return '-';
    if (S_ISDIR(mode))
        return 'd';
    if (S_ISCHR(mode))
        return 'c';
    if (S_ISBLK(mode))
        return 'b';
    if (S_ISLNK(mode))
        return 'l';
    if (S_ISFIFO(mode))
        return 'p';
    if (S_ISSOCK(mode))
        return 's';
    return '?';
}

char *perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "---------"); 

    if (mode & S_IRUSR) perms[0] = 'r';
    if (mode & S_IWUSR) perms[1] = 'w';
    if (mode & S_IXUSR) perms[2] = 'x';
    if (mode & S_IRGRP) perms[3] = 'r';
    if (mode & S_IWGRP) perms[4] = 'w';
    if (mode & S_IXGRP) perms[5] = 'x';
    if (mode & S_IROTH) perms[6] = 'r';
    if (mode & S_IWOTH) perms[7] = 'w';
    if (mode & S_IXOTH) perms[8] = 'x';

    if (mode & S_ISUID) perms[2] = (mode & S_IXUSR) ? 's' : 'S';
    if (mode & S_ISGID) perms[5] = (mode & S_IXGRP) ? 's' : 'S';
    if (mode & S_ISVTX) perms[8] = (mode & S_IXOTH) ? 't' : 'T';

    return perms;
}

void printStat(char *dir_path, char *filename, struct stat *st) {
    struct passwd *pw;
    struct group *gr;
    char *timestr;
    
    if (opt_i) {
        printf("%llu ", (unsigned long long)st->st_ino);
    }
    printf("%5ld ", (long)st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode)); 
    printf("%3lu ", (unsigned long)st->st_nlink);
    
    pw = getpwuid(st->st_uid);
    gr = getgrgid(st->st_gid);
    
    printf("%s %s ", 
           (pw != NULL) ? pw->pw_name : "unknown", 
           (gr != NULL) ? gr->gr_name : "unknown");

    printf("%9ld ", (long)st->st_size);
    
    timestr = ctime(&st->st_mtime);
    printf("%12s ", timestr + 4); 

    if (opt_Q) {
        printf("\"%s\"", filename);
    } else {
        printf("%s", filename);
    }

    if (opt_p && S_ISDIR(st->st_mode)) {
        printf("/");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[PATH_MAX + 1];
    int opt;
    
    while ((opt = getopt(argc, argv, "ipQ")) != -1) {
        switch (opt) {
            case 'i':
                opt_i = 1;
                break;
            case 'p':
                opt_p = 1;
                break;
            case 'Q':
                opt_Q = 1;
                break;
            case '?': 
                fprintf(stderr, "알 수 없는 옵션: -%c\n", optopt);
                return 1;
            default:
                break;
        }
    }
    if (optind < argc)
        dir = argv[optind];
    else 
        dir = ".";
    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }
    while ((d = readdir(dp)) != NULL) {
        snprintf(path, PATH_MAX, "%s/%s", dir, d->d_name); 

        if (lstat(path, &st) < 0) {
            perror(path);
            continue;
        }
        printStat(dir, d->d_name, &st);
    }
    closedir(dp);
    return 0;
}
