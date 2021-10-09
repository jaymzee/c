#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

#define NALLOC 128  // units to allocate at once

typedef struct header { // free block header
    struct header *ptr;  // next free block
    size_t size; // size of this free block
} HEADER;

static HEADER base;             // empty list to get started
static HEADER *allocp = NULL;   // last allocated block

void ffree(void *ap)
{
    HEADER *p, *q;

    p = (HEADER *)ap - 1;   // point to header
    for (q = allocp; !(p > q && p < q->ptr); q=q->ptr) {
        if (q >= q->ptr && (p > q || p < q->ptr)) {
            break;  // at one end or other
        }
    }

    if  (p+p->size == q->ptr) { // join to upper nbr
        p->size += q->ptr->size;
        p->ptr = q->ptr->ptr;
    } else {
        p->ptr = q->ptr;
    }

    if (q+q->size == p) {
        q->size += p->size;
        q->ptr = p->ptr;
    } else {
        q->ptr = p;
    }
    allocp = q;
}

static HEADER *morecore(size_t nu)
{
    void *cp;
    HEADER *up;
    size_t rnu;

    rnu = NALLOC * ((nu+NALLOC-1) / NALLOC);
    cp = sbrk(rnu * sizeof(HEADER));
    if (cp < 0) {
        return NULL;
    }
    up = (HEADER *)cp;
    up->size = rnu;
    ffree(up+1);

    return allocp;
}

void *alloc(size_t nbytes)
{
    HEADER *p, *q;
    size_t nunits;

    nunits = 1 + (nbytes + sizeof(HEADER)-1) / sizeof(HEADER);
    if ((q = allocp) == NULL) { // no free list yet
        base.ptr = allocp = q = &base;
        base.size = 0;
    }

    for (p=q->ptr; ;q=p, p=p->ptr) {
        if (p->size >= nunits) { // big enough
            if (p->size == nunits) { // exactly
                q->ptr = p->ptr;
            } else {
                p->size -= nunits;
                p += p->size;
                p->size = nunits;
            }
            allocp = q;
            return ((char *)(p+1));
        }
        if (p == allocp) { // wrapped around free list
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

    ptr1 = alloc(1);
    ptr2 = alloc(1);
    printf("ptr1: %p\n", ptr1);
    printf("ptr2: %p\n", ptr2);

    p = (HEADER *)ptr1 - 1;
    printf("ptr1 { next: %p, size: %u }\n", p->ptr, p->size);
    p = (HEADER *)ptr2 - 1;
    printf("ptr2 { next: %p, size: %u }\n", p->ptr, p->size);
    printf("allocp { next: %p, size: %u }\n", allocp->ptr, allocp->size);
    printf("base { next: %p, size: %u }\n", base.ptr, base.size);

    ffree(ptr1);
    ffree(ptr2);

    return 0;
}
