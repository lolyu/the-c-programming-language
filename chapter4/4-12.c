#include <stdio.h>
#include <stdlib.h>

char *itoa(int, char [], int);

int main(void) {
    char s[100];
    char *p;
    int n = -10086;
    p = itoa(n, s, 10);
    printf("%s\n", s);
    return 0;
}

char *itoa(int n, char s[], int base) {
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
