#include <stdio.h>
#include <stdlib.h>

/*
 * binary tree array implementation
 * a binary tree can be stored in an array (linearized binary tree)
                 0
           1            2
        3     4      5     6
       7 8   9 10  11 12 13 14

left child = 2 * index + 1
right child = 2 * index + 2
parent = (index - 1) / 2
sibling = (index - 1) ^ 1 + 1
*/


#define LEFT 1
#define RIGHT 2

// 2^n - 1 elements
char tree[15];

void set_root(char key)
{
    if (tree[0]) {
        printf("tree already has a root\n");
    } else {
        tree[0] = key;
    }
}

void set_child(char key, int parent, int side)
{
    int indx = 2 * parent + side;
    if (tree[parent] == 0) {
        printf("Can't set child at %d, no parent found\n", indx);
    } else {
        tree[indx] = key;
    }
}

char fmt_child(int parent, int side)
{
    char c = tree[2 * parent + side];
    return c ? c : ' ';
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

int main()
{
    set_root('A');
    set_child('B', 0, LEFT);
    set_child('C', 0, RIGHT);
    set_child('D', 1, LEFT);
    set_child('E', 1, RIGHT);
    //set_child('F', 2, LEFT);
    set_child('G', 2, RIGHT);

    print_tree(7);

    printf("   %c\n", tree[0]);
    printf(" %c   %c\n", fmt_child(0, LEFT), fmt_child(0, RIGHT));
    printf("%c %c %c %c\n", fmt_child(1, LEFT), fmt_child(1, RIGHT),
                            fmt_child(2, LEFT), fmt_child(2, RIGHT));

    return 0;
}
