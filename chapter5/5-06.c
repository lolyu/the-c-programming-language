#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>


int _getline(char *, int);
int _atoi(char *);
char *itoa(int, char*, int);
void reverse(char*);
int strindex(const char *, const char *);

int main(void) {
    char s[] = "-10020";
    int r = atoi(s);
    char t[100];
    itoa(r, t, 2);
    printf("%d | %s\n", r, t);
    reverse(t);
    printf("%s\n", t);
    printf("%d\n", strindex("helloworld", "world"));
    printf("%d\n", strindex("helloworld", ""));
    printf("%d\n", strindex("helloworld", "hello"));
    printf("%d\n", strindex("helloworld", "hellllo"));
    return 0;
}

int _getline(char *s, int lim) {
    int c;
    char *p = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *p++ = c;
    if (c == '\n')
        *p++ = c;
    *p = 0;
    return (int)(p - s);
}

int _atoi(char *s) {
    int n, sign;
    for (; isspace(*s); ++s);
    sign = (*s == '+' || *s == '-') ? (*s++ == '-' ? -1 : 1) : 1;
    for (n = 0; isdigit(*s); n = n * 10 + (*s++ - '0'));
    return n * sign;
}

char *itoa(int n, char *s, int base) {
    char *p;
    if (abs(n) < base) {
        p = s;
        if (n < 0)
            *p++ = '-';
    }
    else
        p = itoa(n / base, s, base);
    *p++ = "0123456789abcdefghijklmnopqrstuvwxyz"[abs(n) % base];
    *p = '\0';
    return p;
}

void swap(char *l, char *r) {
    char tmp = *l;
    *l = *r;
    *r = tmp;
}

void reverse(char *s) {
    char *p;
    for (p = s; *p; ++p);
    --p;
    for (; p != s; swap(s++, p--));
}

int strindex(const char *source, const char *searchfor) {
    if (*searchfor == '\0')
        return 0;
    char *s0, *s1, *t;
    for (s0 = source; *s0; ++s0) {
        for (s1 = s0, t = searchfor; *t && *s1++ == *t++;);
        if (t != searchfor && *t == '\0')
            return s0 - source;
    }
    return -1;
}
