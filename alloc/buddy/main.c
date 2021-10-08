#include <stdio.h>
#include <stdlib.h>

#define LEFT 1
#define RIGHT 2

#define MEM_MIN_BLOCK 1024
#define MEM_SIZE (16 * 1024)

// 2^n - 1 elements
char tree[31];
char memblk[MEM_SIZE];

void set_child(char key, int parent, int side)
{
    int indx = 2 * parent + side;
    if (tree[parent] == 0) {
        printf("Can't set child at %d, no parent found\n", indx);
    } else {
        tree[indx] = key;
    }
}

void print_tree(int size) {
    for (int i = 0; i < size; i++) {
        if (tree[i] != 0) {
            printf("%c", tree[i]);
        } else {
            printf("-");
        }
    }
    printf("\n");
}

void *buddy(size_t size, void *block, size_t blksize, int id)
{
    if (size > blksize || tree[id] == 'P') {
        return NULL;
    }

    printf("buddy(%d, %p, %d, %d)\n", size, block, blksize, id);
    if (size > blksize / 2) {
        tree[id] = 'P';
        return block;
    } else if (blksize / 2 >= MEM_MIN_BLOCK) {
        tree[id] = 'H';
        void *newblock = buddy(size, block, blksize / 2, 2 * id + 1);
        if (newblock == NULL) {
            newblock = buddy(size, block + blksize / 2, blksize / 2, 2 * id + 2);
        }
        return newblock;
    }

    return NULL;
}

void *alloc(size_t size)
{
    return buddy(size, memblk, MEM_SIZE, 0);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 31; i++) {
        tree[i] = '-';
    }
    tree[0] = 'H';
    print_tree(31);

    void *ptr = alloc(1024);
    void *ptr2 = alloc(1024);
    //void *ptr3 = alloc(1024);

    printf("%d\n", ptr - (void *)memblk);
    printf("%d\n", ptr2 - (void *)memblk);
    //printf("%d\n", ptr3 - (void *)memblk);

    print_tree(31);

    return 0;
}

