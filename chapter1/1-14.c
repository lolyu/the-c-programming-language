#include <stdio.h>

#define CHARCOUNT 128

int main(int argc, char **argv) {
    int c, i, j, max_freq = 0;
    int freq[CHARCOUNT];

    for (i = 0; i < CHARCOUNT; ++i)
        freq[i] = 0;

    while ((c = getchar()) != EOF)
        ++freq[c];

    printf("Horizontal histogram\n\n");
    printf("    char | freq\n");
    for (i = 0; i < CHARCOUNT; ++i) {
        if (!freq[i])
            continue;
        if (max_freq < freq[i])
            max_freq = freq[i];
        printf("     %3d | ", i);
        for (j = 0; j < freq[i]; ++j)
            printf("#");
        printf(" %d\n", freq[i]);
    }

    printf("Vertical histogram\n\n");
    for (j = max_freq; j > 0; --j) {
        printf("  %4d | ", j);
        for (i = 0; i < CHARCOUNT; ++i) {
            if (!freq[i])
                continue;
            if (freq[i] >= j)
                printf("  #");
            else
                printf("   ");
            printf(" ");
        }
        printf("\n");
    }
    printf("---------");
    for (i = 0; i < CHARCOUNT; ++i) {
        if (!freq[i])
            continue;
        printf("----");
    }
    printf("\n         ");
    for (i = 0; i < CHARCOUNT; ++i)
        if (freq[i])
            printf("%3d ", i);
    printf("\n");
}
