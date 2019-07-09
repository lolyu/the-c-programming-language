#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#define PERMS 0666

void error(char *, ...);

int main(int argc, char *argv[]) {
    if (argc != 3)
        error("Usage: cp <src> <dst>");
    int f1, f2, n, i, holes;
    char buf[BUFSIZ];
    if ((f1 = open(argv[1], O_RDONLY, 0)) < 0)
        error("cp: can't open %s", argv[1]);
    if ((f2 = creat(argv[2], PERMS)) < 0)
        error("cp: can't create %s, mode %03o", argv[2], PERMS);
    holes = 0;
    while ((n = read(f1, buf, BUFSIZ)) > 0) {
        for (i = 0; i < n; ++i) {
            if (buf[i] == '\0') {
                ++holes;
                continue;
            }
            if (holes > 0) {
                lseek(f2, holes, SEEK_CUR);
                holes = 0;
            }
            if (write(f2, &buf[i], 1) != 1)
                error("cp: write error on file %s", argv[2]);
        }
        if (write(f2, buf, n) != n)
            error("cp: write error on file %s", argv[2]);
    }
    if (close(f1) < 0)
        error("cp: close error on file %s", argv[1]);
    if (close(f2) < 0)
        error("cp: close error on file %s", argv[2]);
    return 0;
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
