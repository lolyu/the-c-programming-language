#include <stdio.h>

size_t strlen(const char*);
void strcpy(char*, const char*);
void strncpy(char*, const char*, int);
void strcat(char*, const char*);
void strncat(char*, const char*, int);
int strcmp(const char*, const char*);
int strncmp(const char*, const char*, int);
int strend(const char*, const char*);

int main(int argc, char* argv[]) {
	char s0[30] = "helloworld";
	char s1[30] = "hell0w0rld1111";
	strcat(s0, ", my friend.");
	printf("%s\n", s0);
	printf("%d\n", strend(s0, "friend."));
	strncpy(s0, s1, 10);
	printf("%s\n", s0);
	return 0;
}

size_t strlen(const char* s) {
	int i;
	for (i = 0; *(s + i); ++i);
	return i;
}

void strcpy(char* s, const char* t) {
	while (*s++ = *t++);
}

void strncpy(char* s, const char* t, int n) {
	while (*s++ = *t++)
		if (--n == 0)
			break;
	*s = '\0';
}

void strcat(char *s, const char *t) {
	while (*s && ++s);
	strcpy(s, t);
}

void strncat(char* s, const char* t, int n) {
	while (*s && ++s);
	strncpy(s, t, n);
}

int strcmp(const char* s, const char* t) {
	for (; *s == *t; ++s, ++t)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

int strncmp(const char* s, const char* t, int n) {
	for (; *s == *t && n > 0; ++s, ++t, --n)
		if (*s == '\0')
			return 0;
	return n == 0 || *s == *t ? 0 : *s - *t;
}

int strend(const char* s, const char* t) {
	size_t len_a = strlen(s);
	size_t len_b = strlen(t);
	if (len_a < len_b)
		return 0;
	else {
		s += (len_a - len_b);
		return strcmp(s, t) == 0 ? 1: 0;
	}
}
