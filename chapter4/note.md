# chapter4 note
## implicit function return

```c
#include <stdio.h>
#include <string.h>

// If the } that terminates a function is reached, and the value of the function
// call is used by the caller, the behavior is undefined.

int f0() {
    return;
}

int f1() {}

void f2() {
    return;
}

void f3() {}

int main(int argc, char *argv[]) {
    printf("%s\n", f0());
    printf("%s\n", f1());
    printf("%s\n", NULL);
    return 0;
}
```

## references
https://stackoverflow.com/questions/10079089/implicit-int-return-value-of-c-function
