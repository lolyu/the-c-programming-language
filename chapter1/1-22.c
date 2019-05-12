#include <stdio.h>

#define LINESIZE	1001
#define TEXTWIDTH	12
#define SPACE		' '
#define IN			0
#define OUT			1


int getline(char buf[], int len);


int main(int argc, char* argv[]) {
	char line[LINESIZE];
	char folded[LINESIZE];
	int len;
	int i, j, k;
	int last_blank, last_fold, state;
	char c;

	while (len = getline(line, LINESIZE)) {
		printf("LINE:\n%s\n", line);
		state = OUT;
		for (last_blank = last_fold = i = j = 0; i < len; ++i) {
			if (line[i] == SPACE) {
				if (state == IN) {
					state = OUT;
					last_blank = i;
				}
			}
			else {
				state = IN;
				if (i - last_fold + 1 > TEXTWIDTH && last_blank > last_fold) {
					for (k = 0; k < last_blank - last_fold; ++k)
						folded[j++] = line[last_fold + k];
					folded[j++] = '\n';
					for (last_fold = last_blank; last_fold < len && line[last_fold] == SPACE; ++last_fold);
				}
			}
		}
		for (i = last_fold; i < len; folded[j++] = line[i++]);
		printf("FOLDED LINE:\n%s\n", folded);
	}
	return 0;
}


int getline(char buf[], int len) {
	int i;
	char c;

	i = 0;
	while (i < len - 1 && (c = getchar()) != EOF && c != '\n')
		buf[i++] = c;
	if (c == '\n')
		buf[i++] = '\n';
	buf[i] = 0;
	return i;
}
