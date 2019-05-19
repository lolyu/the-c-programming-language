#include <stdio.h>


unsigned setbits(unsigned, int, int, unsigned);
unsigned invert(unsigned, int, int);
unsigned rightrot(unsigned, int);


int main(int argc, char *argv[]) {
    unsigned x = 11;
    unsigned ret = rightrot(x, 2);
    printf("%d\n", ret);
    return 0;
}


unsigned setbits(unsigned x, int p, int n, unsigned y) {
    return (~(~(~0 << n) << (p + 1 - n)) & x) | (y & ~(~0 << n) << (p + 1 - n));
}


unsigned invert(unsigned x, int p, int n) {
    return x ^ (~(~0 << n) << (p + 1 - 1));
}


unsigned rightrot(unsigned x, int n) {
    unsigned bits;
    for (bits = 0; (1 << bits) < x; ++bits);
    n %= bits;
    return (~(~0 << n) & x) << (bits - n) | (x >> n);
}
