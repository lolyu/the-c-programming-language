#include <stdio.h>
#include <stdarg.h>

void minprintf(const char *, ...);

int main(void) {
    minprintf("%d %f %s\n", 10, 100.0, "helloworld");
    printf("helloworld");
    return 0;
}

void minprintf(const char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);
    for (p = fmt; *p; ++p) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                printf("%s", va_arg(ap, char *));
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}
