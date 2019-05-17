#include <stdio.h>


int main(int argc, char *argv[]) {
    return 0;
}


unsigned setbits(unsigned x, int p, int n, unsigned y) {
    return (~(~(~0 << n) << (p + 1 - n)) & x) | (y & ~(~0 << n) << (p + 1 - n));
}

