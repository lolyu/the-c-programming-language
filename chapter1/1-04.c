#include <stdio.h>

#define LOWER -50
#define UPEER 50
#define STEP 5

int main(int argc, char *argv[]) {
    float fahr, celsius;
    printf("%6s %6s\n", "celsius", "fahr");
    for (celsius = LOWER; celsius <= UPEER; celsius += STEP)
        printf("%6.0f %5.1f\n", celsius, 1.8 * celsius + 32.0);
}
