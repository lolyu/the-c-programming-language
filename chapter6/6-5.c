#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>
#include <ctype.h>

#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(const char *);
struct nlist *plookup(const char *);
struct nlist **_lookup(const char *);
struct nlist *lookup(const char *);
struct nlist *install(const char *, const char *);
int undef(const char *);

int main(void) {
    int i;
    char s[][10] = {"name0", "hello", "name1", "world", "name2", "aloha"};
    struct nlist *p;
    for (i = 0; i < 3; ++i)
        install(s[2 * i], s[2 * i + 1]);
    p = lookup("name0");
    printf("%s %s\n", p->name, p->defn);
    p = lookup("name1");
    printf("%s %s\n", p->name, p->defn);
    p = lookup("name2");
    printf("%s %s\n", p->name, p->defn);
    undef("name2");
    p = lookup("name2");
    printf("%p\n", p);
    exit(EXIT_SUCCESS);
}

unsigned hash(const char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; ++s)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist **_lookup(const char *s) {
    struct nlist **np;
    for (np = &hashtab[hash(s)]; *np != NULL; np = &(*np)->next)
        if (strcmp(s, (*np)->name) == 0)
            return np;
    return NULL;
}

struct nlist *lookup(const char *s) {
    struct nlist **np = _lookup(s);
    if (np)
        return *np;
    return NULL;
}

struct nlist *install(const char *name, const char *defn) {
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(struct nlist));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
        free((void *)np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

int undef(const char *s) {
    struct nlist *next;
    struct nlist **np = _lookup(s);
    if (np) {
        next = (*np)->next;
        free((*np)->name);
        free((*np)->defn);
        free(*np);
        *np = next;
        return 0;
    }
    return 1;
}
