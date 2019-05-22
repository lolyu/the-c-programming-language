#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER 0
#define FUNC 1
#define MAXVAL 100
#define BUFSIZE 100

void push(double);
double pop(void);
void clear(void);
void viewtop(void);
void dulicatetop(void);
void swaptoptwo(void);
int getch(void);
void ungetch(int);
int getop(char *);
void to_lower(char *);
int dispatch(char *);


int bufp = 0;
char buf[BUFSIZE];
int sp = 0;
double val[MAXVAL];


int main(int argc, char *argv[]) {
    int type, error;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                push(pop() / op2);
                break;
            case '%':
                op2 = pop();
                push(fmod(pop(), op2));
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            case FUNC:
                error = dispatch(s);
                if (error == 0)
                    break;
            default:
                fprintf(stderr, "error: unkown command %s.\n", s);
                break;
        }
    }
    return 0;
}


void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        fprintf(stderr, "error, stack full, can't push %g.\n", f);
}

double pop(void) {
    if (sp == 0) {
        fprintf(stderr, "error: empty stack.\n");
        return 0.0;
    }
    else
        return val[--sp];
}

void clear(void) {
    sp = 0;
}

void viewtop(void) {
    if (sp == 0)
        fprintf(stderr, "error: empty stack.");
    else
        printf("TOP: %f\n", val[sp - 1]);
}

void dulicatetop(void) {
    if (sp == 0)
        fprintf(stderr, "error: empty stack");
    else {
        double tmp = pop();
        push(tmp);
        push(tmp);
    }
}

void swaptoptwo(void) {
    if (sp < 2)
        fprintf(stderr, "error: less than two elems.");
    else {
        double tmp0, tmp1;
        tmp0 = pop();
        tmp1 = pop();
        push(tmp0);
        push(tmp1);
    }
}

int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    if (isalpha(c)) {
        while (isalpha(s[++i] = c = getch()));
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        return FUNC;
    }
    if (!isdigit(c) && c != '.')
        return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()));
    if (c == '.')
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

int getch(void) {
    return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        fprintf(stderr, "ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}

void to_lower(char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; ++i)
        if (isalpha(s[i]) && s[i] <= 'Z')
            s[i] = 'a' + s[i] - 'A';
}

int dispatch(char s[]) {
    double tmp;
    int error = 0;
    to_lower(s);
    if (strcmp(s, "sin") == 0)
        push(sin(pop()));
    else if (strcmp(s, "cos") == 0)
        push(cos(pop()));
    else if (strcmp(s, "exp") == 0)
        push(exp(pop()));
    else if (strcmp(s, "pow") == 0) {
        tmp = pop();
        push(pow(pop(), tmp));
    }
    else
        error = 1;
    return error;
}
