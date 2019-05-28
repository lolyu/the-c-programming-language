#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define BUFSIZE 100


char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getint(int *);
int getfloat(double *);

int main() {
    int n;
    double d;
    while (getfloat(&d) >= 0)
        printf("GET: %g\n", d);
    return 0;
}


int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        fprintf(stderr, "ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}

int getint(int *pn) {
    int c, sign;
    while (isspace(c = getch()));
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            if (c == EOF)
                return c;
            ungetch(sign == 1 ? '+' : '-');
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int getfloat(double *pf) {
    int c, sign, power;
    while (isspace(c = getch()));
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') {
            if (c == EOF)
                return c;
            ungetch(sign = 1 ? '+' : '-');
            return 0;
        }
    }
    power = 0;
    for (*pf = 0.0; isdigit(c) || c == '.'; c = getch()) {
        if (c == '.')
            power = 1;
        else if (!power)
            *pf = 10 * *pf + (c - '0');
        else
            *pf = *pf + (c - '0') / pow(10, power++);
    }
    *pf *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}
