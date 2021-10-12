#include <stdalign.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#define NALLOC 128  // units to allocate at once

typedef struct header { // free block header
    alignas(2 * sizeof(void *))
    struct header *next;  // next free block
    size_t size; // size of this free block in units
} Header;

static Header base;  // empty list to get started
static Header *freeptr = NULL;   // start of free list

static Header *morecore(size_t nu);
void kr_free(void *ap);

/*
 * allocate memory
 */
void *kr_malloc(size_t nbytes)
{
    Header *currptr, *prevptr;
    size_t nunits;

    /* calculate the number of memory units needed to provide at least
     * nbytes of memory (plus the unit for Header)
     */
    nunits = 1 + (nbytes + sizeof(Header) - 1) / sizeof(Header);

    // case: no free list exists; we have to initialize
    if (freeptr == NULL) {
        // create degenerate free list; base points to itself and has size 0
        base.next = &base;
        base.size = 0;

        // set free list starting point to base address
        freeptr = &base;
    }
    // initialize pointers to two consecutive blocks in the free list
    prevptr = freeptr;
    currptr = prevptr->next;

    /* step through the free list looking for a block of memory large enough
     * to fit nunits of memory. If the list is traversed without finding such
     * a block, then morecore is called to request more memory from the OS.
     */
    for (; ; prevptr = currptr, currptr = currptr->next) {
        /* case: found a block of memory in free list large enough to fit
         * nunits of memory into. Partition block if necessary, remove it from
         * the free list, and return the address of the block (after moving
         * past the header).
         */
        if (currptr->size >= nunits) {
            /* case: block is exactly the right size; remove the block from
             * the free list by pointing the previous block to the next block.
             */
            if (currptr->size == nunits) {
                /* Note that his line wouldn't work as intended if we were
                 * down to only 1 block. However we would never make it here
                 * in that scenario because the block at &base has size 0 and
                 * the conditional will fail.
                 */
                prevptr->next = currptr->next;
            /* case: block is larger than needed; allocate tail end of the
             * block to the user.
             */
            } else {
                // partition off the end of the block and create new header
                currptr->size -= nunits;
                currptr += currptr->size;
                currptr->size = nunits;
                // currptr points the control structure for the block to return
            }
            /* Set global starting position to the previous pointer. Next call
             * to malloc will start either at the remaining part of the
             * partitioned block if a partition occurred or at the block after
             * the selected block if not.
             */
            freeptr = prevptr;
            /* return the location of the start of memory (move past the
             * header)
             */
            return (void *)(currptr + 1);
        }
        /* case: we've wrapped around the free list without finding a block
         * large enough. Call morecore to request more memory from the OS.
         */
        if (currptr == freeptr) {
            /* morecore returns freeptr; the reason we have to assign currptr
             * to it again is that there is a call to free inside morecore that
             * can potentially change freeptr. Thus we reassign so that we can
             * be assured the newly added block is found before
             * (currptr==freeptr) again.
             */
            if ((currptr = morecore(nunits)) == NULL) {
                return NULL;
            }
        }
    }
}

/*
 * ask system for more memory
 */
static Header *morecore(size_t nunits)
{
    void *freemem;      // the address of the newly created memory
    Header *insertp;    // header pointer

    /* Obtaining memory from OS is a comparatively expensive process operation,
     * so obtain at least NALLOC blocks of memory and partition as needed.
     */
    if (nunits < NALLOC) {
        nunits = NALLOC;
    }

    /* Request that the OS increment the program's data space. sbrk changes the
     * location of the program break, which defines the end of the process's
     * data segment.
     */
    freemem = sbrk(nunits * sizeof(Header));
    // case: unable to allocate more memory; sbrk returns -1 on error
    if (freemem < 0) {
        return NULL;
    }

    // construct new block
    insertp = (Header *)freemem;
    insertp->size = nunits;

    /* Insert block into the free list so that it is available for malloc.
     * Note that we add 1 to the address to point the pointer past the header.
     */
    kr_free(insertp + 1);

    /* Returns the start of the free list; recall that freeptr has been set to
     * the block immediately proceeding the newly allocated memory (by free).
     * Thus by returning this value, the calling function can immediately find
     * the new memory by follwing the pointer to the next block.
     */
    return freeptr;
}

/*
 * free memory
 */
void kr_free(void *ptr)
{
    Header *insertp, *currp;


    // find address of block header for the data to be inserted
    insertp = (Header *)ptr - 1;

    /* Step through the free list looking for the position in the list to place
     * the insertion block. In the typical circumstance this would be the block
     * immediately to the left of the insertion block; this checked for by
     * finding a block that is to the left of the insertion block and such that
     * the following block in the list is to the right of the insertion block.
     * However this check doesn't check for one such case, and misses another.
     * We still have to check for the cases where either the insertion block is
     * either to the left of every other block owned by malloc (the case that
     * is missed), or to the right of every block owned by malloc (the case
     * not checked for). These last two cases are what is checked for by the
     * condition inside the loop.
     */
    for (currp = freeptr; !(currp < insertp && insertp < currp->next);
         currp = currp->next) {
        /* currp >= currp->next implies that the current block is the rightmost
         * block in the free list. Then if the insertion block is to the right
         * of that block, then it is the new rightmost block; conversely if it
         * is to the left of the block that currp points to (which is the
         * current leftmost block), then the insertion block is the new
         * leftmost block. Note that this conditional handles the case where
         * we only have 1 block in the free list (this case is the reason that
         * we need >= in the first test rather than just >).
         */
        if (currp >= currp->next &&
            (currp < insertp || insertp < currp->next)) {
            break;  // freed block at start or end of arena
        }
    }

    /* Having found the correct location in the free list to place the
     * insertion block, now we have to (i) link it to the next block, and (ii)
     * link the previous block to it.  These are the tasks of the next two
     * if/else pairs.
     */

    /* case: the end of the insertion block is adjacent to the beginning of
     * another block of data owned by malloc.  Absorb the block on the right
     * into the block on the left (i.e. the previously existing block is
     * absorbed into the insertion block).
     */
    if (insertp + insertp->size == currp->next) { // join to upper nbr
        insertp->size += currp->next->size;
        insertp->next = currp->next->next;
    /* case: the insertion block is not left-adjacent to the beginning of
     * another block of data owned by malloc.  Set the insertion block member
     * to point to the next block in the list.
     */
    } else {
        insertp->next = currp->next;
    }

    /* case: the end of another block of data owned by malloc is adjacent to
     * the beginning of the insertion block.  Absorb the block on the right
     * into the block on the left (i.e. the insertion block is absorbed into
     * the preceeding block).
     */
    if (currp + currp->size == insertp) {
        currp->size += insertp->size;
        currp->next = insertp->next;
    /* case: the insertion block is not right-adjacent to the end of another
     * block of data owned by malloc.  Set the previous block in the list to
     * point to the insertion block.
     */
    } else {
        currp->next = insertp;
    }
    /* Set the free pointer list to start the block previous to the insertion
     * block.  This makes sense because calls to malloc start their search for
     * memory at the next block after freep, and the insertion block has as
     * good a chance as any of containing a reasonable amount of memory since
     * we've just added some to it.  It also coincides with calls to morecore
     * from kandr_malloc because the next search in the iteration looks at
     * exactly the right memory block.
     */
    freeptr = currp;
}

void print_header(const char *prefix, const char *suffix, Header *p)
{
    printf("%sHeader { next: %p, size: %u }%s", prefix, p->next, p->size, suffix);
}

void print_list(Header *list)
{
    for (Header *p = list->next; p != list; p=p->next) {
        print_header("", "\n", p);
    }
}

int main(int argc, char *argv[])
{
    void *ptr1, *ptr2;

    printf("sizeof(Header) = %d\n", sizeof(Header));

    ptr1 = kr_malloc(2048);
    ptr2 = kr_malloc(1024);
    printf("ptr1 = %p\n", ptr1);
    print_header("*ptr1 = ", "\n", (Header *)ptr1 - 1);
    printf("ptr2 = %p\n", ptr2);
    print_header("*ptr2 = ", "\n", (Header *)ptr2 - 1);

    printf("freeptr = %p\n", freeptr);
    print_header("*freeptr = ", "\n", freeptr);
    print_header("*freeptr->next = ", "\n", freeptr->next);
    print_header("base = ", "\n", &base);
    printf("-----------------\n");

    kr_free(ptr1);
    print_list(&base);
    kr_free(ptr2);
    print_list(&base);

    return 0;
}
