#include <stdio.h>
#include <ctype.h>


double atof(char s[]);


int main(int argc, char *argv[]) {
    char num[] = "123.45e-6";
    printf("%g\n", atof(num));
    return 0;
}


double atof(char s[]) {
    double val, power0, power1;
    double *p;
    int i, sign, expo;
    for (i = 0; isspace(s[i]); ++i);
    sign = (s[i] == '-') ? -1: 1;
    if (s[i] == '-' || s[i] == '+')
        ++i;
    for (val = 0.0; isdigit(s[i]); ++i)
        val = val * 10.0 + s[i] - '0';
    if (s[i] == '.')
        ++i;
    power0 = power1 = 1.0;
    for (power1 = 1.0; isdigit(s[i]); ++i) {
        val = val * 10.0 + s[i] - '0';
        power1 *= 10.0;
    }
    if (s[i] == 'e' || s[i] == 'E') {
        expo = (int)atof(s + i + 1);
        if (expo > 0) {
            p = &power0;
        }
        else {
            p = &power1;
            expo *= -1;
        }
        for (; expo > 0; --expo)
            *p *= 10;
    }
    return sign * val * power0 / power1;
}
