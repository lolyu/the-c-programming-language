# note chapter 5

## operator precedence and associativity

```c
#include <stdio.h>

int main()
{
    int arr[] = {10, 20};
    int *p = arr;
    printf("%d\n", ++*p);                       // 11
    p = arr;
    printf("%d\n", *++p);                       // 20
    p = arr;
    printf("%d\n", *p++);                       // 11
    printf("%d %d %d\n", arr[0], arr[1], *p);   // 11 20 20
    return 0;
}
```

* `prefix ++` and `*` has same precedence, with left-to-right associativity.
* `postfix ++` has higher precedence than both `*` and `prefix ++`, `postfix ++` has right-to-left associativity.
