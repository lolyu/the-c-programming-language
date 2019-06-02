#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXVAL 100

void push(double);
double pop(void);

int main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stdout, "please enter expression.\n");
		exit(EXIT_FAILURE);
	}

	double op2;
	++argv, --argc;
	for (; argc > 0; ++argv, --argc) {
		switch (**argv) {
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			push(atof(*argv));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			op2 = pop();
			push(pop() / op2);
			break;
		case '\0':
		default:
			fprintf(stderr, "unknow operator: %c", **argv);
			exit(EXIT_FAILURE);
		}
	}
	printf("result: %g\n", pop());
	return 0;
}

int sp = 0;
double val[MAXVAL];

void push(double d) {
	if (sp >= MAXVAL)
		fprintf(stderr, "error: stack full, fail to push %g.\n", d);
	else
		val[sp++] = d;
}

double pop(void) {
	if (sp <= 0) {
		fprintf(stderr, "error: empty stack.\n");
		return 0.0;
	}
	else
		return val[--sp];
}
