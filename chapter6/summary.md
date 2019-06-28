# struct

## initialization
```c
struct point p1 = {0, 0};
struct point p2 = {100, 100};
struct point p3 = addpoint(p1, p2);
struct point p4; p4 = {200, 200};       
struct point p5; p5 = (struct point) {.x = 101, .y = 101};
```
* `p4` initialization is illegal.
* `p5` initialization is new in C99.

## operator precedence
* `.`, `->`, `()` and `[]` are at the top of the precedence hierarchy.
* `++p->len`: increment `len` instead of `p`.
* `*p->str` fetches whatever `str` points to.
* `*p->str++` increments `str` after accessing whatever `str` points to.
* `(*p->str)++` is same as `*p->str++`.
* `*p++->str` increments `p` after accessing whatever `str` points to.

## sizeof
* When `sizeof`'s operand is a type, it has to be enclosed in parentheses. But when `sizeof`'s operand is a variable, this is not required.
  * `sizeof(type)`
  * `sizeof variable`

## union
```c
#include <stdio.h>
#include <stdlib.h>

#define INT     0
#define FLAOT   1
#define STRING  2

struct {
    unsigned int is_keyword : 1;
    unsigned int is_extern : 1;
    unsigned int is_static : 1;
} flags;

struct entry {
    struct nlist *next;
    char *name;
    int utype;
    union value {
        int iv;
        double dv;
        char *sv;
    } u;
};

int main(void) {
    return 0;
}
```
* `union` could only be initialized with a value of the type of its first memeber.
* it is the programmer's responsibility to track which type is currently stored in a `union`.

## fields
```c
struct {
    unsigned int is_keyword : 1;
    unsigned int is_extern : 1;
    unsigned int is_static : 1;
} flags;
```
* if `int` is 4 bytes, above `fields` will take 4 bytes, as soon as you have 33 bit field in it, it will expands to 8 bytes.

## references
https://stackoverflow.com/questions/26652791/sizeof-vs-sizeof-in-standard-c

