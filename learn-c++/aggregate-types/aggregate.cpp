#include <iostream>

// The following code has the same semantics in both C and C++

struct C {
    int a;
    double b;
};

struct D {
    int a;
    double b;
    C c;
};

// initialize an object of type C with an initializer-list
C c = {1, 2.0};

// D has a sub-aggregate of type C. In such cases initializer-clauses
// can be nested.
D d = {10, 20.0, {1, 2.0}};

int main()
{
   using std::cout;
   cout << "an aggregate type is a type with no user-declared\n"
        << "constructors, no private or protected non-static data\n"
        << "members, no base classes, and no virtual functions.\n"
        << "Such a class can be initialized with a brace-enclosed\n"
        << "comma-separated list of initializer-clauses.\n";
}
