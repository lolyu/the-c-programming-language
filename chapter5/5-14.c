#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES        5000
char *lineptr[MAXLINES];
int fold = 0;
int dir = 0;
int reverse = -1;


int readlines(char *[], int);
void writelines(char *[], int);

void _qsort(void **, int, int, int(*)(void *, void *));
int numcmp(const char *, const char *);
int _strcmp(const char *, const char *);
void err_prompt();

int main(int argc, char *argv[]) {
    int nlines;
    int i;
    int numeric = 0;
    for (i = 1; i < argc; ++i) {
        if (*argv[i] == '-') {
            switch (*(argv[i] + 1)) {
                case 'n': numeric = 1; break;
                case 'r': reverse = 1; break;
                case 'f': fold = 1; break;
                case 'd': dir = 1; break;
                default: err_prompt();
            }
        }
        else
            err_prompt();
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        for (i = 0; i < nlines; ++i)
            printf("LINE: %s\n", lineptr[i]);
        _qsort((void **)lineptr, 0, nlines - 1,
                (int (*)(void*, void*))(numeric ? numcmp : _strcmp));
        writelines(lineptr, nlines);
        exit(EXIT_SUCCESS);
    }
    else {
        fprintf(stderr, "input too big to sort\n");
        exit(EXIT_FAILURE);
    }
}


void err_prompt() {
    char usage[] = "Usage: sort [OPTION]\n"
                   "Sort lines from stdin.\n\n"
                   "   -r\treverse order\n"
                   "   -n\tcompares based on leading numeric value\n"
                   "   -d\tcompares only on letters, numbers and blanks\n"
                   "   -f\tfold upper and lower case togather\n";
    fprintf(stderr, "%s", usage);
    exit(EXIT_FAILURE);
}

int numcmp(const char *s1, const char *s2) {
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

int _strcmp(const char *s1, const char *s2) {
    int c1, c2;
    while (*s1 && *s2) {
        if (dir) {
            if (!(isdigit(*s1) || isalpha(*s1) || isspace(*s1)))
                ++s1;
            if (!(isdigit(*s2) || isalpha(*s2) || isspace(*s2)))
                ++s2;
            continue;
        }
        c1 = *s1++, c2 = *s2++;
        if (fold && c1 >= 'A' && c1 <= 'Z')
            c1 = c1 - 'A' + 'a';
        if (fold && c2 >= 'A' && c2 <= 'Z')
            c2 = c2 - 'A' + 'a';
        if (c1 != c2)
            return (c1 - c2) / abs(c1 - c2);
    }
    if (*s1)
        return 1;
    else if (*s2)
        return -1;
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
    int i, last, cmp;
    void swap(void *[], int, int);
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left; i <= right; ++i)
        if (reverse * (*comp)(v[i], v[left]) > 0)
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
    while (maxlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}
