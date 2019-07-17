#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NALLOC 1024

typedef double Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    }s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

void *_malloc(unsigned);
void *_calloc(unsigned, unsigned);
static Header *morecore(unsigned);
void _free(void *);

int main(void) {
    char *p;
    p = _malloc(1024 * sizeof(char));
    if (p == NULL) {
        fprintf(stderr, "error allocate space\n");
        exit(EXIT_FAILURE);
    }
    strcpy(p, "helloworld");
    printf("%s\n", p);
    return 0;
}

void *_malloc(unsigned nbytes) {
    Header *p, *prev;
    unsigned nunits;
    nunits = (nbytes - 1) / sizeof(Header) + 2;
    if ((prev = freep) == NULL) {
        base.s.ptr = p = prev = freep = &base;
        base.s.size = 0;
    }
    for (p = prev->s.ptr;;prev = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits) {
                prev->s.ptr = p->s.ptr;
            } else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prev;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

void *_calloc(unsigned nunit, unsigned usize) {
    void *p = NULL;
    p = malloc(nunit * usize);
    if (NULL != p)
        memset(p, 0x00, nunit * usize);
    return p;
}

static Header *morecore(unsigned nunits) {
    char *cp;
    Header *up;
    if (nunits < NALLOC)
        nunits = NALLOC;
    cp = sbrk(nunits * sizeof(Header));
    if (cp == (char *) -1)
        return NULL;
    up = (Header *)cp;
    up->s.size = nunits;
    _free((void *)(up + 1));
    return freep;
}

void _free(void *ap) {
    Header *bp, *p;
    bp = (Header *)ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p->s.ptr <= p && (bp > p || bp < p->s.ptr))
            break;
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;       // due to line 89
    } else
        p->s.ptr = bp;
    freep = p;
}
