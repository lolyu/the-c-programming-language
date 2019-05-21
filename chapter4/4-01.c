#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

const char pattern[] = "ould";

int _getline(char line[], int max);
int strindex(char source[], char searchfor[]);
int strrindex(char source[], char searchfor[]);


int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int index, found = 0;
    while ((index = _getline(line, MAXLINE)) > 0) {
        if ((index = strrindex(line, pattern)) >= 0) {
            printf("%d: %s", index, line);
            ++found;
        }
    }
    printf("\nfound %d line%s.\n", found, found > 1 ? "s": "");
    return 0;
}


int _getline(char line[], int max) {
    int i, c;
    i = 0;
    while (i < max && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}


int strindex(char source[], char searchfor[]) {
    int i, j, k;
    for (i = 0; source[i]; ++i) {
        for (j = 0, k = i; source[k] == searchfor[j]; ++k, ++j);
        if (j > 0 && searchfor[j] == '\0')
            return i;
    }
    return -1;
}


int strrindex(char source[], char searchfor[]) {
    int i, j, k;
    for (i = strlen(source) - strlen(searchfor) - 1; i >= 0; --i) {
        for (k = i, j = 0; source[k] == searchfor[j]; ++k, ++j);
        if (j > 0 && searchfor[j] == '\0')
            return i;
    }
    return -1;
}
