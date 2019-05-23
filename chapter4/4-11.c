#include <stdio.h>
#define NUMBER 0


int getop(char s[]) {
    static int c = ' ';
    int i, ret;
    while (c == ' ' || c == '\t')
        c = getchar();
    s[0] = c;
    s[1] = '\0';
    if (isalpha(c)) {
        while (isalpha(s[++i] = c = getchar()));
        s[i] = '\0';
        return FUNC;
    }
    if (!isdigit(c) && c != '.') {
        ret = c;
        c = ' ';
        return ret;
    }
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()));
    if (c == '.')
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    return NUMBER;
}
