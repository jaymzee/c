#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

#define NALLOC 128  // units to allocate at once

typedef struct header { // free block header
    struct header *ptr;  // next free block
    size_t size; // size of this free block in units
} HEADER;

static HEADER base;            // empty list to get started
static HEADER *freep = NULL;   // start of free list

void kr_free(void *ap)
{
    HEADER *bp, *p;

    bp = (HEADER *)ap - 1;   // point to block header
    for (p = freep; !(bp > p && bp < p->ptr); p=p->ptr) {
        if (p >= p->ptr && (bp > p || bp < p->ptr)) {
            break;  // freed block at start or end of arena
        }
    }

    if  (bp + bp->size == p->ptr) { // join to upper nbr
        bp->size += p->ptr->size;
        bp->ptr = p->ptr->ptr;
    } else {
        bp->ptr = p->ptr;
    }

    if (p + p->size == bp) {
        p->size += bp->size;
        p->ptr = bp->ptr;
    } else {
        p->ptr = bp;
    }
    freep = p;
}

/*
 * ask system for more memory
 */
static HEADER *morecore(size_t nu)
{
    void *cp;
    HEADER *up;
    size_t rnu;

    if (nu < NALLOC) {
        nu = NALLOC;
    }
    //rnu = NALLOC * ((nu+NALLOC-1) / NALLOC);
    cp = sbrk(nu * sizeof(HEADER));
    if (cp < 0) {
        return NULL;
    }
    up = (HEADER *)cp;
    up->size = nu;
    kr_free(up+1);

    return freep;
}

void *kr_malloc(size_t nbytes)
{
    HEADER *p, *prevp;
    size_t nunits;

    nunits = 1 + (nbytes + sizeof(HEADER) - 1) / sizeof(HEADER);
    if ((prevp = freep) == NULL) { // no free list yet
        base.ptr = freep = prevp = &base;
        base.size = 0;
    }

    for (p=prevp->ptr; ;prevp=p, p=p->ptr) {
        if (p->size >= nunits) { // big enough
            if (p->size == nunits) { // exactly
                prevp->ptr = p->ptr;
            } else { // allocate tail end
                p->size -= nunits;
                p += p->size;
                p->size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep) { // wrapped around free list
            if ((p = morecore(nunits)) == NULL) {
                return NULL; // none left
            }
        }
    }
}

int main(int argc, char *argv[])
{
    void *ptr1, *ptr2;
    HEADER *p;

    printf("sizeof(HEADER) = %d\n", sizeof(HEADER));

    ptr1 = kr_malloc(3);
    ptr2 = kr_malloc(1024);
    printf("ptr1: %p\n", ptr1);
    printf("ptr2: %p\n", ptr2);

    p = (HEADER *)ptr1 - 1;
    printf("ptr1 { next: %p, size: %u }\n", p->ptr, p->size);
    p = (HEADER *)ptr2 - 1;
    printf("ptr2 { next: %p, size: %u }\n", p->ptr, p->size);
    printf("allocp { ptr: %p, size: %u }\n", freep->ptr, freep->size);
    printf("allocp->ptr { ptr: %p, size: %u }\n", freep->ptr->ptr, freep->ptr->size);
    printf("base { next: %p, size: %u }\n", base.ptr, base.size);

    kr_free(ptr1);
    kr_free(ptr2);

    return 0;
}
