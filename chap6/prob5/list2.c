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
#define PATH_MAX 4096

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

void printStat(char *pathname, char *file, struct stat *st) {
    struct passwd *pw;
    struct group *gr;
    char *timestr;
    
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
    printf("%s\n", file);
}

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[PATH_MAX + 1];
    
    if (argc == 1)
        dir = ".";
    else 
        dir = argv[1];

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }
    
    while ((d = readdir(dp)) != NULL) { 
        
        snprintf(path, PATH_MAX, "%s/%s", dir, d->d_name);

        if (lstat(path, &st) < 0) {
            perror(path);
        } else {
            printStat(path, d->d_name, &st);
        }
    } 

    closedir(dp);
    exit(0);
}
