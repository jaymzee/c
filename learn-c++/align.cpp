#include <iostream>

struct alignas(16) Node {
    int value;
    Node *next;
    void print_all();
};

void Node::print_all()
{
    for (Node *ptr = this; ptr != NULL; ptr = ptr->next) {
        if (ptr != this) {
            std::cout << " -> ";
        }
        std::cout << ptr << " (" << ptr->value << ")";
    }
    std::cout << std::endl;
}

int main()
{
    Node nodes[3] = { 42, NULL, 88, NULL, 33, NULL };
    Node *head;

    head = &nodes[0];
    nodes[0].next = &nodes[1];
    nodes[1].next = &nodes[2];

    std::cout << sizeof(Node) << std::endl;
    head->print_all();

    return 0;
}
