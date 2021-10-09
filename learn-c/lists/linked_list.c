#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

typedef struct Node Node;

void insert_at_head(Node **head, Node *item)
{
    item->next = *head;
    *head = item;
}

void append_at_tail(Node **head, Node *item)
{
    if (*head == NULL) {
        *head = item;
        return;
    }

    Node *p = *head;
    while (p->next != NULL) {
        p = p->next;
    }

    p->next = item;
}

Node *create_node(int value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    return node;
}

int main(int argc, char *argv[])
{
    for (int n = 0; n < argc; n++) {
        printf("argv[%d] = \"%s\"\n", n, argv[n]);
    }

    Node *head = NULL;
    insert_at_head(&head, create_node(1));
    insert_at_head(&head, create_node(2));
    //append_at_tail(&head, create_node(1));
    //append_at_tail(&head, create_node(2));

    for (Node *ptr = head; ptr != NULL; ptr = ptr->next) {
        printf("%d\n", ptr->value);
    }


    return 0;
}
