#include <stdio.h>
#include "node.h"

int main()
{
    struct Node *node1 = CreateNode(42);

    AttachNode(AttachNode(node1, CreateNode(88)), CreateNode(55));

    PrintNodes(node1);

    return 0;
}
