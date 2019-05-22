#include <string.h>
#include <stdio.h>

#define BUFSIZE 100

int cache = EOF;

int getch(void) {
    char ret;
    if (cache >= 0) {
        ret = cache;
        cache = EOF;
    }
    else
        ret = getchar();
    return ret;
}

void ungetch(int c) {
    cache = c;
}


int main(void) {
    char c;
    ungetch('L');
    while ((c = getch()) != EOF)
        putchar(c);
    return 0;
}
