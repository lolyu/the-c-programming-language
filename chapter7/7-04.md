#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int minscanf(const char *, ...);

int main(void) {
    int i, count;
    double d;
    char *s;
    s = (char *)malloc(100 * sizeof(char));
    count = minscanf("%d %f %s", &i, &d, s);
    printf("\n%d %f %s\n", i, d, s);
    return 0;
}

int minscanf(const char *fmt, ...) {
    char *p, *sp;
    int *ip, count;
    double *dp;
    va_list ap;

    va_start(ap, fmt);
    count = 0;
    for (p = fmt; *p; ++p) {
        if (*p != '%')
            continue;
        switch (*++p) {
            case 'd':
                ip = va_arg(ap, int*);
                count += scanf("%d", ip);
                break;
            case 'f':
                dp = va_arg(ap, double*);
                count += scanf("%lf", dp);
                break;
            case 's':
                sp = va_arg(ap, char*);
                count += scanf("%s", sp);
                break;
            default:
                break;
        }
    }
    return count;
}
