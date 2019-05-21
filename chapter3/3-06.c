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


void itob(int n, char s[], unsigned w) {
    int i, sign = 0;
    if (sign = (n < 0))
        n = -n;
    s[i = 0] = '\0';

    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign)
        s[i++] = '-';
    for (i; i < w; s[i++] = ' ');
    s[i] = '\0';
    reverse(s);
}


int main(int argc, char *argv[]) {
    char s[100];
    itob(-1000, s, 10);
    printf("%s\n", s);
    return 0;
}
