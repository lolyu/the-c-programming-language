#include <stdio.h>


int htoi(const char s[]) {
	int i, n;
	int count[128];
	for (i = 0; i < 128; ++i)
		if (i >= '0' && i <= '9')
			count[i] = i - '0';
		else if (i >= 'A' && i <= 'F')
			count[i] = i - 'A' + 10;
		else if (i >= 'a' && i <= 'f')
			count[i] = i - 'a' + 10;
		else
			count[i] = 0;
	i = 0;
	if (s[0] == '0') {
		if (s[1] == 'x' || s[1] == 'X')
			i += 2;
		else
			return -1;
	}

	for (n = 0; s[i] != '\0'; ++i) {
		if (s[i] != '0' && count[s[i]] == 0)
			return -1;
		n = n * 16 + count[s[i]];
	}
	return n;
}


int main(int argc, char *argv[]) {
	const char* test[] =
	{
	  "F00",
	  "bar",
	  "0100",
	  "0x1",
	  "0XA",
	  "0X0C0BE",
	  "abcdef",
	  "123456",
	  "0x123456",
	  "deadbeef",
	  "zog_c"
	};
	int i;

	for (i = 0; i < 11; ++i)
		printf("%10s:\t%d\n", test[i], htoi(test[i]));
	return 0;
}
