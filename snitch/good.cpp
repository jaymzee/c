#include <iostream>
#include "Snitch.h"

/*
Always delete copy constructor on polymorphic classes
create a clone method instead
*/

struct A : public Snitch {
    A(int id) : Snitch(id) { log(" A ctor"); }
    A(const A&) = delete;
    A& operator=(const A&) = delete;
    ~A() { log(" A dtor"); }
    virtual char m() { return 'A'; }
};

struct B : public A {
    B(int id) : A(id) { log("  B ctor"); }
    ~B() { log("  B dtor"); }
    char m() override { return 'B'; }
};

void f(A& a)
{
    auto a2 = a; // oops, slices the object, but caught by compiler

    std::cout << "in f()" << std::endl;
    std::cout << a.m() << std::endl;
    std::cout << a2.m() << std::endl;
}

int main(int argc, char *argv[])
{
    B b{1};
    std::cout << "calling f with " << b.m() << std::endl;
    f(b);

    return 0;
}
