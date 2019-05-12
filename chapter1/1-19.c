#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1001


int getline(char buf[], int len);
void reverse(char buf[]);
void swap(char* a, char* c);


int main(int argc, char* argv[]) {
	char line[MAXLINE];
	int len;
	while (len = getline(line, MAXLINE)) {
		reverse(line);
		printf("REVERSED:\n%s\n", line);
	}
	return 0;
}


int getline(char buf[], int len) {
	int i = 0;
	char c;
	for (; i < len && (c = getchar()) != EOF && c != '\n'; buf[i++] = c);
	if (c == '\n')
		buf[i++] = c;
	buf[i] = 0;
	if (i == len - 1)
		for (; (c = getchar()) != EOF && c != '\n'; ++i);
	return i;
}


void reverse(char buf[]) {
	int len = strlen(buf);
	char tmp;
	int i, j;
	for (i = 0, j = len - 1; i < j; swap(&buf[i++], &buf[j--]));
}


void swap(char* a, char* b) {
	char tmp = *a;
	*a = *b;
	*b = tmp;
}
