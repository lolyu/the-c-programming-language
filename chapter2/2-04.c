#include <stdio.h>


#define CHARSET 128


void squeeze(char s1[], const char s2[]);


int main(int argc, char *argv[]) {
	const char* test1[] = {
		" h",
		"ow",
		"mf"
	};
	int i;
	for (i = 0; i < 3; ++i) {
		char test0[] = "hello world, my friend.";
		printf("s1: %s, s2: %s", test0, test1[i]);
		squeeze(test0, test1[i]);
		printf(" after squeeze: %s\n", test0);
	}
	return 0;
}


void squeeze(char s1[], const char s2[]) {
	int occurence[CHARSET];
	int i, j;
	for (i = 0; i < CHARSET; occurence[i++] = 0);
	for (i = 0; s2[i] != '\0'; occurence[s2[i++]] = 1);
	for (i = j = 0; s1[i] != '\0'; ++i)
		if (occurence[s1[i]] == 0)
			s1[j++] = s1[i];
	s1[j] = '\0';
}
