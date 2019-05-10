#include <stdio.h>

#define LOWER 0
#define UPEER 300
#define STEP 20

double fahr_to_cel(double);

int main(int argc, char *argv[]) {
    float fahr, celsius;
    printf("%4s %6s\n", "fahr", "celsius");
    for (fahr = LOWER; fahr <= UPEER; fahr += STEP)
        printf("%4.0f %6.1f\n", fahr, fahr_to_cel(fahr));
}

double fahr_to_cel(double fahr) {
    return (5.0/9.0) * (fahr-32.0);
}
