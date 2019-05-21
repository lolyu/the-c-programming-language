#include <stdio.h>
#include <string.h>


const char bits[] = "0123456789abcdefghijklmnopqrstuvwxyz";


void reverse(char s[]) {
    size_t i, j;
    char c;
    for (i = 0, j = strlen(s) - 1; i < j; ++i, --j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void itob(int n, char s[], unsigned b) {
    int i, sign = 0;
    if (sign = (n < 0))
        n = -n;
    s[i = 0] = '\0';
    if (b > strlen(bits) || b <= 0)
        return;
    do {
        s[i++] = bits[n % b];
    } while ((n /= b) > 0);
    if (sign)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


int main(int argc, char *argv[]) {
    char s[100];
    itob(-1000, s, 16);
    printf("%s\n", s);
    return 0;
}
