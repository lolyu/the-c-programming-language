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
