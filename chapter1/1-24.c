#include <stdio.h>
#include <stdlib.h>


#define STACKSIZE 1001


int getline_(char line[], int len);


char stack[STACKSIZE];
int top = 0;


int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./a.out <C source file>\n");
        exit(EXIT_FAILURE);
    }
    char *filename = argv[1];

    FILE * fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open input file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    char c, t;
    int matched = 0;
    int line = 1;
    stack[top] = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == 34 || c == 39) {
            for (;  fgetc(fp) != c;);
            continue;
        }
        if (c == '\n')
            ++line;
        if (c == '[' || c == '{' || c == '(') {
            stack[top++] = c;
            stack[top] = 0;
        }
        else if (c == ']' || c == '}' || c == ')') {
            if (top <= 0) {
                fprintf(stderr, "LINE %d: no match for %c\n", line, c);
                exit(EXIT_FAILURE);
            }
            t = stack[top - 1];
            if (c == ')')
                matched = (c - t == 1);
            else
                matched = (c - t == 2);
            if (matched) {
                stack[--top] = 0;
            }
            else {
                fprintf(stderr, "LINE %d: unmatch for %c, cached: %s\n", line, c, stack);
                exit(EXIT_FAILURE);
            }
        }
    }
    printf("Matched source file: %s\n", filename);
    return 0;
}
