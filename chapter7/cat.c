#include <stdio.h>
#include <stdlib.h>

void filecopy(FILE *src, FILE *dest) {
    int c;
    while ((c = fgetc(src)) != EOF) {
        c = fputc(c, dest);
        if (ferror(dest)) {
            perror("fputc");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1)
        filecopy(stdin, stdout);
    else {
        FILE *fp;
        for (++argv; --argc > 0;) {
            fp = fopen(*argv, "r");
            if (fp == NULL) {
                perror("fopen");
                exit(EXIT_FAILURE);
            }
            filecopy(fp, stdout);
            fclose(fp);
        }
    }
    if (ferror(stdout)) {
        perror("error writing stdout");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
