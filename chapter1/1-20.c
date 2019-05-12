#include <stdio.h>


#define TABSIZE 5
#define TAB		'\t'
#define SPACE	' '


int main(int argc, char* argv[]) {
	int i;
	int c;
	int count;

	printf("-------------------------------------\n");
	count = 0;
	while ((c = getchar()) != EOF) {
		if (c == TAB) {
			for (i = 0; i < TABSIZE - count; ++i)
				putchar(SPACE);
			count = 0;
		}
		else if (c == '\n') {
			putchar(c);
			count = 0;
		}
		else {
			putchar(c);
			count = (count + 1) % TABSIZE;
		}
	}

	return 0;
}
