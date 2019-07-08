#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE            1000
#define LINES_PER_PAGE  10
char line[LINESIZE];

void print_file(const char *);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "no file specified.\n");
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = 1; i < argc; ++i)
        print_file(argv[i]);
    exit(EXIT_SUCCESS);
}

void print_file(const char *filename) {
    int lineno, pageno;
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    lineno = 0, pageno = 1;
    while (fgets(line, LINESIZE, fp) != NULL) {
        if (lineno % LINES_PER_PAGE == 0) {
            if (pageno > 1)
                printf("[%s] page %d ends\n", filename, pageno - 1);
            printf("[%s] page %d starts\n", filename, pageno);
            ++pageno;
        }
        printf("%4d: %s", ++lineno, line);
    }
    printf("\n[%s] page %d ends\n", filename, pageno - 1);
}
