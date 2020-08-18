#include <stdio.h>
#include <stdlib.h>

void cat_file(FILE *fp, int flush) {
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        fputc(ch, stdout);
        if (flush && ch == '\n')
            fflush(stdout);
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        /* for each file */
        for (int i = 1; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (!fp) {
                /* show error message and quit */
                fprintf(stderr, "%s: ", argv[0]);
                perror(argv[i]);
                exit(2);
            }
            /* write file to stdout */
            cat_file(fp, 0);
            fclose(fp);
        }
        exit(0);
    }

    if (argc == 1) {
        /*
        unbuffered writes when reading from stdin (send character immediately)
        setvbuf(stdout, NULL, _IONBF, 0);
        or just flush output when a newline is received from stdin
        */
        cat_file(stdin, 1);
        exit(0);
    }

    fprintf(stderr, "Usage: cat [FILE]...[FILE]...\n");
    exit(1);
}
