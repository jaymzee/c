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
   cout << "An aggregate class is called a POD if it has no user-defined\n"
        << "copy-assignment operator, destructor, and none of it's nonstatic\n"
        << "members is a non-POD class, array of non-POD, or a reference.\n";
}
