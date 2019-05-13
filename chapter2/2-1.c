#include <stdio.h>
#include <limits.h>
#include <float.h>


int main(int argc, char *argv) {
    printf("signed char min: %d\n", SCHAR_MIN);
    printf("signed char max: %d\n", SCHAR_MAX);
    printf("unsigned char max: %d\n", UCHAR_MAX);
    printf("char min: %d\n", CHAR_MIN);
    printf("char max: %d\n", CHAR_MAX);
    printf("short min: %d\n", SHRT_MIN);
    printf("short max: %d\n", SHRT_MAX);
    printf("unsigned short int max: %d\n", USHRT_MAX);
    printf("int min: %d\n", INT_MIN);
    printf("int max: %d\n", INT_MAX);
    printf("unsigned int max: %d\n", UINT_MAX);
    printf("long min: %ld\n", LONG_MIN);
    printf("long max: %ld\n", LONG_MAX);
    printf("unsigned long max: %lu\n", ULONG_MAX);
    printf("float min: %g\n", FLT_MIN);
    printf("float max: %g\n", FLT_MAX);
    printf("double min: %g\n", DBL_MIN);
    printf("double max: %g\n", DBL_MAX);
    printf("long double min: %Lg\n", LDBL_MIN);
    printf("long double max: %Lg\n", LDBL_MAX);
    return 0;
}
