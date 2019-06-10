#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES        5000
char *lineptr[MAXLINES];

int readlines(char *[], int);
void writelines(char *[], int);

void _qsort(void **, int, int, int(*)(void *, void *));
int numcmp(char *, char *);


int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0;
    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        _qsort((void **)lineptr, 0, nlines - 1,
                (int (*)(void*, void*))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        exit(EXIT_SUCCESS);
    }
    else {
        fprintf(stderr, "input too big to sort\n");
        exit(EXIT_FAILURE);
    }
}

int numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void _qsort(void *v[], int left, int right, int(*comp)(void *, void *)) {
    int i, last;
    void swap(void *[], int, int);
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left; i <= right; ++i)
        if ((*comp)(v[left], v[i]) > 0)
            swap(v, ++last, i);
    swap(v, left, last);
    _qsort(v, left, last - 1, comp);
    _qsort(v, last + 1, right, comp);
}

#define MAXLEN      1000
int _getline(char *, int);

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int _getline(char *s, int limit) {
    int c;
    char *p = s;
    while (--limit > 0 && (c = getchar()) != EOF && c != '\n')
        *p++ = c;
    if (c == '\n')
        *p++ == c;
    *p = '\0';
    return (int)(p - s);
}

void writelines(char *lineptr[], int maxlines) {
    while (--maxlines > 0) {
        printf("%s\n", *lineptr++);
    }
}
