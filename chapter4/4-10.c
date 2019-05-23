#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define MAXVAL 100
#define NUMBER '0'
#define MAXLINE 100

int getop(char []);
void push(double);
double pop(void);
int _getline(char [], int);

char line[MAXLINE];
int lp;
double val[MAXVAL];
int sp = 0;

int main(void) {
    int type;
    double op2;
    char s[MAXOP];
    while (_getline(line, MAXLINE) > 0) {
        lp = 0;
        while ((type = getop(s)) != '\0') {
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
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("error: zero divisor\n");
                    break;
                case '\n':
                    printf("\t%.8g\n", pop());
                    break;
                default:
                    printf("error: unknown command \'%s\'\n", s);
                    break;
            }
        }
    }
    return 0;
}

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        fprintf(stderr, "error: stack full, can't push %g.\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else
        fprintf(stderr, "error: empty stack.\n");
    return 0.0;
}

int _getline(char s[], int lim) {
    int i, c;
    for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; s[i++] = c);
    if (c == '\n')
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}

int getop(char s[]) {
    int i, c;
    while ((s[0] = c = line[lp++]) == ' ' || c == '\t');
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = line[lp++]));
    if (c == '.')
        while (isdigit(s[++i] = c = line[lp++]));
    s[i] = '\0';
    --lp;
    return NUMBER;
}
