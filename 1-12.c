#include <stdio.h>

int main(int argc, char *argv[]) {
    int c, state, count;
    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (++count == 1)
                putchar('\n');
        }
        else {
            count = 0;
            putchar(c);
        }
    }
}
