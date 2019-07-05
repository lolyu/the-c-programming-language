#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE 1000
#define MISMATCH_FAILURE    1
#define USAGE_FAILURE       2
#define ALLOC_SPACE_FAILURE 3
#define FILE_OPEN_FAILURE   4
#define FILE_READ_FAILURE   5

void error_exit(const char *, int);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: diff <file> <file>\n");
        exit(USAGE_FAILURE);
    }
    FILE *fp0, *fp1;
    int lineno, len;
    char *s0, *s1;
    char *line0 = (char *)malloc(LINE * sizeof(char));
    char *line1 = (char *)malloc(LINE * sizeof(char));
    if (line0 == NULL || line1 == NULL) {
        fprintf(stderr, "failed to allocate space");
        exit(USAGE_FAILURE);
    }
    fp0 = fopen(argv[1], "r");
    if (fp0 == NULL)
        error_exit(argv[0], FILE_OPEN_FAILURE);
    fp1 = fopen(argv[2], "r");
    if (fp1 == NULL)
        error_exit(argv[1], FILE_OPEN_FAILURE);
    lineno = 1;
    while (1) {
        s0 = fgets(line0, LINE, fp0);
        s1 = fgets(line1, LINE, fp1);
        if (((s0 == NULL) ^ (s1 == NULL)) || s0 && s1 && strcmp(s0, s1) != 0) {
            fprintf(stdout, "LINE %d mismatch\n", lineno);
            fprintf(stdout, "< %s", s0 == NULL ? "\n" : s0);
            fprintf(stdout, "> %s", s1 == NULL ? "\n" : s1);
        }
        if (feof(fp0) || feof(fp1) || ferror(fp0) || ferror(fp1))
            break;
        ++lineno;
    }
    return 0;
}

void error_exit(const char *errmsg, int exit_code) {
    perror(errmsg);
    exit(exit_code);
}
