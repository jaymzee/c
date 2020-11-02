#include <iostream>
#include <memory>

class Resource {
    std::string _name;
public:
    Resource(std::string name) : _name(std::move(name)) {
        std::cout << "Resource " << _name << " acquired\n";
    }
    ~Resource() { std::cout << "Resource " << _name << " destroyed\n"; }
    int magic_number() { return 42; }
    friend std::ostream& operator<<(std::ostream& os,
                                    const Resource& r) {
        os << "Resource " << r._name;
        return os;
    }
};

struct Worker {
    std::unique_ptr<Resource> resource_ptr;
    void do_work() {
        if (resource_ptr) {
            //
            std::cout << "Worker::do_work " << *resource_ptr << std::endl;
        } else {
            throw "Worker::doWork I have no resource to work on";
        }
    }
};

void do_something(const std::unique_ptr<Resource>& r)
{
    if (r) {
        std::cout << "do_something(" << *r << ")" << std::endl;
        std::cout << r->magic_number() << std::endl;
    }
}

int main()
{
    Worker w;
    auto r = std::make_unique<Resource>("vram");

    do_something(r);
    w.resource_ptr = std::move(r);
    w.do_work();
    if (!r)
        std::cout << "main: I don't have access to the resource" << std::endl;
    r = std::move(w.resource_ptr);
    if (r) {
        std::cout << "main: Now I have access to the resource" << std::endl;
        std::cout << " " << r->magic_number() << std::endl;
    }
}
