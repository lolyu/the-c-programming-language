#include <string.h>
#include <stdio.h>

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        fprintf(stderr, "ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}


int main(void) {
    char c;
    ungetch(EOF);
    while ((c = getch()) != EOF)
        putchar(c);
    return 0;
}
