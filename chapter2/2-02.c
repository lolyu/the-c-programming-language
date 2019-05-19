#include <stdio.h>


#define MAXLINE 1001


int getline(char buf[], int len) {
    int i, c;
    for (i = 0; i < len - 1; buf[i++] = c) {
        if ((c = getchar()) == EOF)
            break;
        if (c == '\n')
            break;
    }
    if (c == '\n')
        buf[i++] = c;
    buf[i] = 0;
    return i;
}

int main(int argc, char *argv[]) {
    char buf[MAXLINE];
    int len;

    while (len = getline(buf, MAXLINE))
        printf("\n%s\n", buf);
    return 0;
}


