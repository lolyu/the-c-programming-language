#include <stdio.h>

#define LOWER 0
#define UPEER 300
#define STEP 20

int main(int argc, char *argv[]) {
    float fahr, celsius;
    printf("%4s %6s\n", "fahr", "celsius");
    for (fahr = LOWER; fahr <= UPEER; fahr += STEP)
        printf("%4.0f %6.1f\n", fahr, (5.0/9.0) * (fahr-32.0));
}
