#include <stdio.h>

int main(int argc, char *argv[]) {
    int c;
    int count;
    for (count = 0; (c = getchar()) != EOF;) {
        if (c == ' ')
            count += 1;
        else
            count = 0;
        if (count <= 1)
            putchar(c);
    }
}
