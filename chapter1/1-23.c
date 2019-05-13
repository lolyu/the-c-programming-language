#include <stdio.h>

#define MAXLINE 1000


int getline_(char line[], int len);


int main(int argc, char **argv) {
    int len;
    char line[MAXLINE];
    int i;
    int in_comment, in_quote;

    in_comment = in_quote = 0;
    while ((len = getline_(line, MAXLINE)) > 0)
    {
        i = 0;
        while (i < len) {
            if (line[i] == '"')
                in_quote ^= 1;
            if (!in_quote) {
                if (line[i] == '/' && line[i + 1] == '*') {
                    i += 2;
                    in_comment = 1;
                }
                if (line[i] == '*' && line[i + 1] == '/') {
                    i += 2;
                    in_comment = 0;
                }
                if (!in_comment)
                    printf("%c", line[i++]);
                else
                    ++i;
            }
            else {
                printf("%c", line[i++]);
            }
        }
    }
    return 0;
}


int getline_(char line[], int len) {
    char c;
    int i;
    for (i = 0; i < len - 1 && ((c = getchar()) != EOF) && c != '\n'; ++i)
            line[i] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}
