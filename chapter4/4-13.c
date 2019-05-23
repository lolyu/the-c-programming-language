#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char []);
void reverse_helper(char [], size_t, size_t);

int main(void) {
    char s[] = "helloworld";
    reverse(s);
    printf("%s\n", s);
    return 0;
}

void reverse_helper(char s[], size_t start, size_t end) {
    if (start >= end)
        return;
    char tmp;
    tmp = s[start], s[start] = s[end], s[end] = tmp;
    reverse_helper(s, start + 1, end - 1);
}

void reverse(char s[]) {
    size_t len = strlen(s);
    reverse_helper(s, 0, len - 1);
}
