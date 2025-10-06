#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp_in, *fp_out;
    int c;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fp_in = fopen(argv[1], "r");
    if (fp_in == NULL) {
        fprintf(stderr, "Error: Cannot open source file '%s' for reading.\n", argv[1]);
        perror("fopen (source)");
        return EXIT_FAILURE;
    }

    fp_out = fopen(argv[2], "a"); 
    if (fp_out == NULL) {
        fprintf(stderr, "Error: Cannot open destination file '%s' for appending.\n", argv[2]);
        perror("fopen (destination)");
        fclose(fp_in);
        return EXIT_FAILURE;
    }

    while ((c = fgetc(fp_in)) != EOF) {
        fputc(c, fp_out);
    }
    
    fclose(fp_in);
    fclose(fp_out);

    return 0;
}
