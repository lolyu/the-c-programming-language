#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int getchar0(void) {
    char c;
    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

int getchar1(void) {
    static char buf[BUFSIZ];
    static char *bufp;
    static int n = 0;
    if (n == 0) {
        n = read(0, buf, BUFSIZ);
        bufp = buf;
    }
    return --n >= 0 ? (unsigned char)*bufp++ : EOF;
}


int main(void) {
    return 0;
}
