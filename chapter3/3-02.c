#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void escape(char *s, char *t) {
    int i, j;
    for (i = j = 0; t[j]; ++i, ++j) {
        switch(t[j]) {
            case '\n': {
                s[i++] = '\\';
                s[i] = 'n';
                break;
            }
            case '\t': {
                s[i++] = '\\';
                s[i] = 't';
                break;
            }
            default: {
                s[i] = t[j];
                break;
            }
        }
    }
    s[i] = t[j];
}


int main(int argc, char *argv[]) {
    char text1[50] = "\aHello,\n\tWorld! Mistakee\b was \"Extra 'e'\"!\n";
    char text2[51];
    escape(text2, text1);
    printf("%s\n", text2);
    return 0;
}

