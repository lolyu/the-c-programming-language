#include <stdio.h>


int bitcount(unsigned);


int main(int argc, char *argv[]) {
    unsigned x = 0;
    printf("%d\n", bitcount(x));
    return 0;
}


int bitcount(unsigned x) {
    int bits;
    for (bits = 0; x; ++bits, x &= (x - 1));
    return bits;
}
