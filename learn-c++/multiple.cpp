#include <iostream>

class Foo {
public:
    virtual void foo() {}
};

class Bar {
public:
    virtual void bar() {}
};

class Baz {
public:
    virtual void baz() {}
};

class Apple : public Foo, public Bar, public Baz {
};

int main(int argc, char *argv[])
{
    Apple *a = new Apple();

    std::cout << sizeof(*a) << " " << sizeof(a) << std::endl;
    std::cout << a << std::endl;
    std::cout << static_cast<Foo*>(a) << std::endl;
    std::cout << static_cast<Bar*>(a) << std::endl;
    std::cout << static_cast<Baz*>(a) << std::endl;
    return 0;
}

