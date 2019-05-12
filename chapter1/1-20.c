#include <stdio.h>


#define MAXLINE 1001
#define TABSIZE 5
#define TAB		'\t'
#define SPACE	' '

int main(int argc, char* argv[]) {
	int i;
	int c;
	int retval;
	
	while ((c = getchar()) != EOF)
		if (c == TAB)
			for (i = 0; i < TABSIZE; ++i)
				putchar(SPACE);
		else
			putchar(c);

	return 0;
}
