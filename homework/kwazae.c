#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

int main(int argc, char *argv[]) {
    int opt;
    char *value;

    if (argc == 1) {
        for (char **env = environ; *env != NULL; env++) {
            printf("%s\n", *env);
        }
        return 0;
    }

    while ((opt = getopt(argc, argv, "eu:gip")) != -1) {
        switch (opt) {
            case 'e':
                if (optind < argc) { 
                    value = getenv(argv[optind]);
                    if (value)
                        printf("%s = %s\n", argv[optind], value);
                    else
                        printf("No such environment variable: %s\n", argv[optind]);
                } else {
                    for (char **env = environ; *env != NULL; env++)
                        printf("%s\n", *env);
                }
                break;

            case 'u':
                printf("My Realistic User ID : %d(%s)\n", getuid(), getenv("USER"));
                printf("My Valid User ID : %d(%s)\n", geteuid(), getenv("USER"));
                break;

            case 'g':
                printf("My Realistic Group ID : %d(%s)\n", getgid(), getenv("USER"));
                printf("My Valid Group ID : %d(%s)\n", getegid(), getenv("USER"));
                break;

            case 'i':
                printf("my process number : [%d]\n", getpid());
                break;

            case 'p':
                printf("my parent's process number : [%d]\n", getppid());
                break;

            default:
                fprintf(stderr, "Usage: %s [-e var] [-u] [-g] [-i] [-p]\n", argv[0]);
                exit(1);
        }
    }

    return 0;
}

