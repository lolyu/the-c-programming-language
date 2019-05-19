#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define MAX_SIZE 2000000
#define MAX_LOOP 1000000


int binsearch0(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (v[mid] < x)
            low = mid + 1;
        else if (v[mid] > x)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}


int binsearch1(int x, int v[], int n) {
    int low, high, mid;
    low = 0, high = n - 1;
    mid = low + (high - low) / 2;
    while (low <= high && v[mid] != x) {
        if (v[mid] < x)
            low = mid + 1;
        else if (v[mid] > x)
            high = mid - 1;
        mid = low + (high - low) / 2;
    }
    if (x == v[mid])
        return mid;
    return -1;
}


int main(int argc, char *argv[]) {
    int i;
    clock_t start_t, end_t, total_t;
    int v[MAX_SIZE], ret;

    for (i = 0; i < MAX_SIZE; ++i)
        v[i] = i;

    start_t = clock();
    for (i = 0; i < MAX_LOOP; ++i)
        ret = binsearch0(10, v, MAX_SIZE);
    end_t = clock();
    total_t = end_t - start_t;
    printf("binsearch0: %lu\n", total_t);

    start_t = clock();
    for (i = 0; i < MAX_LOOP; ++i)
        ret = binsearch1(10, v, MAX_SIZE);
    end_t = clock();
    total_t = end_t - start_t;
    printf("binsearch1: %lu\n", total_t);
    return 0;
}

