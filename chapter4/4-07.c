#include <string.h>
#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        fprintf(stderr, "ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}

void ungets(const char s[]) {
    int i = strlen(s);
    for (; i > 0; ungetch(s[--i]));
}


int main(void) {
    char c;
    char s[] = "helloworld";
    ungets(s);
    while ((c = getch()) != EOF)
        putchar(c);
    return 0;
}
