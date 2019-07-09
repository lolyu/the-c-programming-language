#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

void error(char *, ...);
void filecopy(int, int);

int main(int argc, char *argv[]) {
    int fd;
    if (argc == 1)
        filecopy(0, 1);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) < 0)
                error("cat: can't open %s", *argv);
            else {
                filecopy(fd, 1);
                if (close(fd) < 0)
                    error("cat: can't close %s", *argv);
            }
    exit(EXIT_SUCCESS);
}

void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(EXIT_FAILURE);
}

void filecopy(int fp1, int fp2) {
    int c;
    while (read(fp1, &c, 1) > 0)
        if (write(fp2, &c, 1) != 1)
            error("cat: write error");
}
