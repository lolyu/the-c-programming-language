#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int (*fp)(int) = NULL;
    int c, i;
    for (i = 0; i < strlen(argv[0]); tolower(argv[0][i++]));
    if (strcmp(argv[0], "./tolower") == 0)
        fp = &tolower;
    else if (strcmp(argv[0], "./toupper") == 0)
        fp = &toupper;
    else {
        fprintf(stderr, "unsupported op");
        exit(EXIT_FAILURE);
    }
    while ((c = getchar()) != EOF)
        putchar((*fp)(c));
    exit(EXIT_SUCCESS);
}
