#include <stdio.h>
#include <string.h>


void expand(char s1[], char s2[]);


int main(int argc, char *argv[]) {
    char s1[] = "-a-z0-9-10";
    char s2[100];
    expand0(s1, s2);
    printf("%s\n%s\n", s1, s2);
    return 0;
}


void expand(char s1[], char s2[]) {
    int i, j, occupied;
    char start_c, end_c, c;
    occupied = -1;
    for (i = j = 0; i < strlen(s1);) {
        printf("%d %d %c %d\n", i, j, s1[i], occupied);
        if (s1[i] == '-' && i - occupied > 1) {
            start_c = s1[i - 1], end_c = s1[i + 1];
            if ((start_c >= 'a' && start_c <= end_c && end_c <= 'z') ||
                (start_c >= 'A' && start_c <= end_c && end_c <= 'Z') ||
                (start_c >= '0' && start_c <= end_c && end_c <= '9')) {
                for (c = start_c + 1; c <= end_c; s2[j++] = c++);
                occupied = ++i;
                ++i;
                continue;
            }
        }
        s2[j++] = s1[i++];
    }
    s2[j] = s1[i];
}
