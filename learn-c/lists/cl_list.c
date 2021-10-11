/*
 * Circular linked lists
 *
 * these can be used to build stacks (with push and pop)
 *
 * features simple and efficient branch free insertion
 * by using the same type for the list and the nodes
 * (an empty list is a node that points to itself)
 */

#include <stdio.h>


struct list {
    struct list *next;
    /* Node value, the value on the list itself is ignored */
    int value;
};

/*
 * initialize empty list
 */
void list_init(struct list *list)
{
    list->next = list;
}

/*
 * insert the entry in the beginning of the list
 */
void list_push(struct list *list, struct list *entry)
{
    struct list *next = list->next;
    entry->next = next;
    list->next = entry;
}

/*
 * remove and return the first entry in the list
 */
struct list *list_pop(struct list *list)
{
    struct list *top = list->next;
    if (top == list) {
        return NULL;
    }
    list->next = top->next;
    return top;
}

/*
 * prints the list by popping all elements off of it
 */
void print_list(struct list *list)
{
    struct list *entry;

    while ((entry = list_pop(list)) != NULL) {
        printf("%d\n", entry->value);
    }
}

int main(int argc, char *argv[])
{
    struct list stack;
    struct list a, b;

    list_init(&stack);

    a.value = 42;
    list_push(&stack, &a);
    b.value = 88;
    list_push(&stack, &b);

    print_list(&stack);

    return 0;
}
