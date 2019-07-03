# summary

## format string
### syntax
```
%[parameter][flags][width][.precision][lenght]type
```
#### parameter field
```c
#include <stdio.h>

int main(void) {
    printf("%2$d %2$#x; %1$d %1$#x",16,17);         // 17 0x11; 16 0x10
}
```

#### flags field
```c

```
