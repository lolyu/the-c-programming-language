#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>
#include <ctype.h>

#define MAXWORD 100

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
    struct tnode *desc;
};

int getword(char *, int);
struct tnode *talloc(void);
struct tnode *addtree(struct tnode *, char *, int prefix);
void treeprint(struct tnode *);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: prefixgrp <prefix length>\n");
        exit(EXIT_FAILURE);
    }
    int prefix;
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    prefix = atoi(argv[1]);
    while (getword(word, MAXWORD) != EOF) {
        printf("%s\n", word);
        if (strlen(word) >= prefix && isalpha(word[0]))
            root = addtree(root, word, prefix);
    }
    treeprint(root);
    exit(EXIT_SUCCESS);
}

int getword(char *word, int lim) {
    int c;
    char *w = word;
    while (isspace(c = getchar()));
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; ++w) {
        if (!isalnum(*w = getchar())) {
            ungetc(*w, stdin);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

struct tnode *talloc(void) {
    struct tnode *temp = (struct tnode *)malloc(sizeof(struct tnode));
    temp->left = temp->right = temp->desc = NULL;
    temp->count = 0;
    return temp;
}

struct tnode *addtree(struct tnode *p, char *w, int prefix) {
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = strndup(w, prefix);
        if (prefix == INT_MAX)
            p->count = 1;
        else
            p->desc = addtree(p->desc, w, INT_MAX);
    }
    else if ((cond = strncmp(w, p->word, prefix)) == 0) {
        if (prefix == INT_MAX)
            ++p->count;
        else
            p->desc = addtree(p->desc, w, INT_MAX);
    }
    else if (cond < 0)
        p->left = addtree(p->left, w, prefix);
    else
        p->right = addtree(p->right, w, prefix);
    return p;
}

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        if (p->count == 0) {
            printf("PREFIX: %s\n", p->word);
            treeprint(p->desc);
        }
        else
            printf("   %4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}
