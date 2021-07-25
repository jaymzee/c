#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct Node {
    int value;
    struct Node *next;
};

struct Node *CreateNode(int value)
{
    struct Node *node = malloc(sizeof(struct Node));

    node->value = value;
    node->next = NULL;

    return node;
}

struct Node *AttachNode(struct Node *a, struct Node *b) {
    a->next = b;
    return b;
}

void PrintNode(struct Node *node)
{
    printf("<Node value=%d>", node->value);
}

void PrintNodes(struct Node *node)
{
    while (node) {
        PrintNode(node);
        printf(" -> ");
        node = node->next;
    }
    printf("null\n");
}
