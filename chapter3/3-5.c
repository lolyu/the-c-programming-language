#include <stdio.h>
#include <string.h>


void reverse(char s[]) {
    size_t i, j;
    char c;
    for (i = 0, j = strlen(s) - 1; i < j; ++i, --j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void itoa(int n, char s[]) {
    int i, sign = 0;
    long int li = n;
    if (li < 0)
        li = -li, sign = 1;
    i = 0;
    do {
        s[i++] = li % 10 + '0';
    } while ((li /= 10) > 0);
    if (sign)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


int main(int argc, char *argv[]) {
    char s[100];
    itoa(-2147483648, s);
    printf("%s\n", s);
    return 0;
}
