#include <stdio.h>

int main(int argc, char *argv[]) {
    int b;
    char c;
    printf("EOF: %d\n", EOF);
    while (1) {
        b = ((c = getchar()) != EOF);
        printf("c = %c, (getchar() != EOF) = %d\n", c, b);
        if (!b)
            break;
    }
}
