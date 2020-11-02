#include "../../snitch/Snitch.h"
#include <iostream>

class Foo: public Snitch {
    int resource;
public:

    explicit Foo(int x):Snitch(x), resource(x) {}
    Foo(const Foo& src):Snitch(src), resource(src.resource) {
        std::cout << "Foo::copy ctor\n";
    }
    Foo(Foo&& src):Snitch(std::move(src)), resource(src.resource) {
        src.resource = 0;
        std::cout << "Foo::move ctor\n";
    }
    ~Foo() {
        if (resource > 0) {
            std::cout << "Foo::freeing resource " << resource << std::endl;
        }
    }
};

Foo foo(Foo f)
{
    std::cout << "inside foo()\n";
    return f;
}

int main(int argc, char *argv[])
{
    Foo h = foo(Foo(1));

    std::cout << "done\n";
}
