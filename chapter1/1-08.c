#include <stdio.h>

int main(int argc, char *argv[]) {
    int c, nl, nt, nb;
    // single quote with single character is a single char literal
    // double quote wit single character contains the char literal and
    // null terminator
    for (nl = nb = nt = 0; (c = getchar()) != EOF;) {
        switch (c) {
            case ' ':
                nb++;
                break;
            case '\t':
                nt++;
                break;
            case '\n':
                nl++;
                break;
        }
    }
    printf("blank count: %d\n", nb);
    printf("tab count: %d\n", nt);
    printf("newline count: %d\n", nl);
}
