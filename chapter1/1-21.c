#include <stdio.h>

#define TABSIZE 5
#define TAB		'\t'
#define SPACE	' '


int main(int argc, char* argv[]) {
	int c;
	int count;

	printf("----------------------------------\n");
	count = 0;
	while ((c = getchar()) != EOF) {
		if (c == SPACE) {
			if (++count == TABSIZE) {
				putchar('\t');
				count = 0;
			}
		}
		else {
			for (; count > 0; --count)
				putchar(SPACE);
			putchar(c);
		}
	}

	return 0;
}
