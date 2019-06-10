#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_LINES       10
#define MAXLINE             1000


int _getline(char *line, int max);
char *dupstr(const char*);


int main(int argc, char *argv[]) {
    int lineno = DEFAULT_LINES;
    if (argc > 1) {
        lineno = atoi(argv[1]);
        if (lineno > 0) {
            fprintf(stderr, "Usage: tail -n\n");
            exit(EXIT_FAILURE);
        }
        lineno = -lineno;
    }

    int len, i, j;
    char **lines = malloc(lineno * sizeof(char*));
    char **current;
    if (!lines) {
        fprintf(stderr, "Fail to allocate space\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < lineno; lines[i++] = NULL);

    current = lines;
    char line[MAXLINE];
    while ((len = _getline(line, MAXLINE)) > 0) {
        printf("%p\n", current);
        if (*current)
            free(*current);
        *current = dupstr(line);
        if (!*current) {
            fprintf(stderr, "Fail to allocate space\n");
            exit(EXIT_FAILURE);
        }
        ++current;
        if (current - lines >= lineno)
            current = lines;
    }
    while (*current) {
        printf("%s", *current);
        free(*current);
        *current++ = NULL;
        if (current - lines >= lineno)
            current = lines;
    }
    return 0;
}

int _getline(char *line, int max) {
    int c;
    char *p = line;
    while (--max > 0 && (c = getchar()) != '\n' && c != EOF)
        *p++ = c;
    if (c == '\n')
        *p++ = c;
    *p = '\0';
    return (int)(p - line);
}

char *dupstr(const char *s) {
    char *p = malloc((strlen(s) + 1) * sizeof(char));
    if (p)
        strcpy(p, s);
    return p;
}
