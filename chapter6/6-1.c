#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

// noise comment: int int int
/* noise comment: int int int */
#ifndef CN
#define CN
int a;
int b;
#endif

struct key {
    char *word;
    int count;
} keytab[] = {
        { "auto", 0 }, { "break", 0 }, { "case", 0 }, { "char", 0 },
        { "const", 0 }, { "continue", 0 }, { "default", 0 }, { "double", 0 }, { "else", 0 },
        { "enum", 0 }, { "extern", 0 }, { "float", 0 }, { "for", 0 },
        { "goto", 0 }, { "if", 0 }, { "int", 0 }, { "long", 0 },
        { "register", 0 }, { "return", 0 }, { "short", 0 }, { "signed", 0 },
        { "sizeof", 0 }, { "static", 0 }, { "struct", 0 }, { "switch", 0 },
        { "typedef", 0 }, { "union", 0 }, { "unsigned", 0 }, { "void", 0 },
        { "volatile", 0 }, { "while", 0 }
};

#define NKEYS (sizeof keytab / sizeof keytab[0])

int getword(char *, int);
struct key *binsearch(char *, struct key *, int);

int main(void) {
    struct key *pos;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        printf("%s\n", word);
        if (isalpha(word[0]))
            if ((pos = binsearch(word, keytab, NKEYS)))
                pos->count++;
    }
    printf("HERE\n");
    for (pos = keytab; pos < keytab + NKEYS; ++pos)
        if (pos->count > 0)
            printf("%4d %s\n", pos->count, pos->word);
    return 0;
}

int getword(char *word, int limit) {
    char c, n;
    while (isspace(c = getchar()));
    if (c != EOF)
        *word++ = c;
    if (!isalpha(c)) {
        if (c == '"' || c == '\'')
            while ((n = getchar()) != c);
        else if (c == '/') {
            n = getchar();
            if (n == '/')
                while ((n = getchar()) != '\n');
            else if (n == '*') {
                while (c != '*' || n != '/') {
                    c = n;
                    n = getchar();
                }
            }
            else
                ungetc(n, stdin);
        }
        else if (c == '#')
            while ((n = getchar()) != '\n');
        *word = 0;
        return c;
    }
    for (; --limit > 0; ++word) {
        if (!(isalnum(*word = getchar()) || *word == '_')) {
            ungetc(*word, stdin);
            break;
        }
    }
    *word = '\0';
    return word[0];
}

struct key *binsearch(char *word, struct key tab[], int n) {
    int cond;
    struct key *left = tab;
    struct key *right = tab + n;
    struct key *mid;
    while (left < right) {
        mid = left + (right - left) / 2;
        if ((cond = strcmp(word, mid->word)) < 0)
            right = mid;
        else if (cond > 0)
            left = mid + 1;
        else
            return mid;
    }
    return NULL;
}
