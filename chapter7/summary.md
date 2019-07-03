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
|character|description|
|-|-|
|-|left-align|
|+|prepend sign|
|' '(space)|space for positive, '-' for negative|
|0|prepend zeros if width is present|
|#|'g' and 'G': reserve trailing zeros; 'f', 'F', 'e', 'E', 'g', 'G': reserve decimal point; 'x', 'X': prepend '0x' or '0X'; 'o': prepend '0'|

```c
#include <stdio.h>

int main(void) {
	printf("%10s\n", "hello");
	printf("%-10s\n", "hello");			// left align
	printf("%+d\n", 100);				// prepend sign: + for positive
	printf("%+d\n", -100);				// prepend sign: - for negative
	printf("% d\n", 100);				// space for positive
	printf("% d\n", -100);				// - for negative
	printf("%010s\n", "hello");			// 0 to prepend zeros when width is specified
	printf("%g\n", 100.100);			// 100.1
	printf("%#g\n", 100.100);			// 100.100 - trailing zeros are reserved
	printf("%#f\n", 0.0);				// alwayts reserve decimal point
	printf("%#x\n", 100);				// with 0x
	return 0;
}
```

#### width field
dynamic width field
```c
#include <stdio.h>

int main(void) {
	printf("%*s", 10, "hello");         // '     hello'
	return 0;
}
```

#### precision field
* for string type, it limits the number of characters that should be output.
* for floating point types, it specifies the digits' count after decimal point.
