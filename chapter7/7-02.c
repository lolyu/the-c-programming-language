#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define LINEWIDTH 10

void failure_exit(const char *);

int main(int argc, char *argv[]) {
    int i, j, n, space;
    int limit = 1000;
    char *line = (char *)malloc(limit * sizeof(char));
    char *output = (char *)malloc(limit * sizeof(char));
    if (!line || !output)
        failure_exit("fail to allocate space");

    while ((n = getline(&line, &limit, stdin)) >= 0) {
        if (n >= (sizeof(output) / sizeof(output[0]))) {
            output = realloc(output, (n * 2) * sizeof(char));
            if (!output)
                failure_exit("fail to allocate space");
        }
        space = -1;
        for (i = 0, j = 0; i < n; ++i) {
            if (i < LINEWIDTH && isspace(line[i]))
                space = j;
            else if (i >= LINEWIDTH && space >= 0)
                output[space] = '\n';
            if (isgraph(line[i]))
                output[j++] = line[i];
            else {
                sprintf(output + j, "0x%02x", line[i]);
                j += 4;
            }
        }
        output[j] = '\0';
        printf("\n%s\n", output);
    }
}

void failure_exit(const char *msg) {
    fprintf(stderr, msg);
    exit(EXIT_FAILURE);
}
