#include <stdio.h>


int lower(int);


int main(int argc, char *argv[]) {
    char c = 'D';
    printf("%c\n", lower(c));
    return 0;
}


int lower(int c) {
    return c >= 'A' && c <= 'Z' ? c - 'A' + 'a': c;
}
