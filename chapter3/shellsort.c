#include <stdio.h>


void shellsort(int v[], int n) {
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; ++i) {
            // keep elements separated by gap in order
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int nums[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int i;

    shellsort(nums, 10);

    for (i = 0; i < 10; ++i)
        printf("%d ", nums[i]);
    printf("\n");
    return 0;
}

