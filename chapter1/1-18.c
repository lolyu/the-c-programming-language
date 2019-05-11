#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1001

int advance(int pointer) {
	if (pointer < MAXLINE - 1)
		return pointer + 1;
	return 0;
}


int main(int argc, char* argv[]) {
	char line[MAXLINE];
	int head, tail;
	int nonspace;
	int retval;
	int c;
	
	retval = nonspace = head = tail = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			head = tail = 0;
			if (nonspace)
				putchar(c);
			nonspace = 0;
		}
		else if (c == ' ' || c == '\t') {
			if (advance(head) == tail) {
				putchar(line[tail]);
				tail = advance(tail);
				retval = EXIT_FAILURE;
			}
			line[head] = c;
			head = advance(head);
		}
		else {
			while (tail != head) {
				putchar(line[tail]);
				tail = advance(tail);
			}
			nonspace = 1;
			putchar(c);
		}
	}
	return retval;
}
