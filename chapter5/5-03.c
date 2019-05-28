#include <stdio.h>


void strcat(char*, const char*);

int main(int argc, char* argv[]) {
	char s0[30] = "helloworld";
	strcat(s0, ", my friend.");
	printf("%s\n", s0);
	return 0;
}

void strcat(char *s, const char *t) {
	while (*s && ++s);
	while (*s++ = *t++);
}
