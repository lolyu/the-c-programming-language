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


## C Right-Left Rule
http://cseweb.ucsd.edu/~ricko/rt_lt.rule.html  
|symbol|read as|
|-|-|
|`*`|pointer to|
|`[]`|array of|
|`()`|function returning|

### STEPS
1. identifier is
2. look to the right till run out of symbols or hit an unmatched right parenthesis.
3. look to the left till run out of symbols or hit an left parenthesis.
4. **REPEAT** 2 and 3 to form declaration.

### EXAMPLE
```c
int (*(*fun_one)(char *,double))[9][20];
```
1. `fun_one` is
2. `fun_one` is pointer to
3. `fun_one` is pointer to function expecting (char *, double) and returning pointer to array size of 9 of array size of 20 of int.

```c
int daytab[2][13];
```
* `daytab` is array(size 2) of array(size 13) of int.
* in short, `daytab` is an array of int with 2 * 13.

```c
int (*daytab)[13];
```
* `daytab` is pointer to array of size 13 of int.
* in short, `daytab` is a pointer to array of 13 integers.




## references:
http://cseweb.ucsd.edu/~ricko/rt_lt.rule.html  
