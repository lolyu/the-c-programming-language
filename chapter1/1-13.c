#include <stdio.h>

#define MAX_LENGTH 16

int main(int argc, char **argv) {
    int c, i, j, count = 0, max_count = 0;
    int freq[MAX_LENGTH + 2];

    for (i = 0; i < MAX_LENGTH + 2; ++i)
        freq[i] = 0;

    while ((c = getchar()) != EOF) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            ++count;
        } else {
            if (count) {
                i = count > MAX_LENGTH ? MAX_LENGTH + 1 : count;
                if (++freq[i] > max_count)
                    max_count = freq[i];
                count = 0;
            }
        }
    }

    printf("\nHorizontal histogram:\n\n");
    for (i = 1; i < MAX_LENGTH + 2; ++i) {
        if (freq[i] == 0)
            continue;
        if (i == MAX_LENGTH + 1)
            printf("   >%2d | : ", MAX_LENGTH);
        else
            printf("    %2d | : ", i);
        for (j = 0; j < freq[i]; ++j)
            printf("#");
        printf(" %d\n", freq[i]);
    }
    
    printf("\nVertical histogram:\n\n");
    for (count = max_count; count > 0; --count) {
        printf("  %2d |  ", count);
        for (i = 1; i < MAX_LENGTH + 2; ++i) {
            if (!freq[i])
                continue;
            if (freq[i] >= count)
                printf("##");
            else
                printf("  ");
            printf(" ");
        }
        printf("\n");
    }
    printf("--------");
    for (i = 1; i < MAX_LENGTH + 2; ++i)
        if (freq[i])
            printf("---");
    printf("\n");
    printf("        ");
    for (i = 1; i < MAX_LENGTH + 2; ++i)
        if (freq[i])
            if (i <= MAX_LENGTH)
                printf("%2d ", i);
            else
                printf(">%2d", MAX_LENGTH);
    printf("\n");
}
