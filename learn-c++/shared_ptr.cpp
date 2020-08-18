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
    std::shared_ptr<Resource> resource_ptr = nullptr;

    void do_work() {
        if (resource_ptr) {
            //
            std::cout << "Worker::do_work " << *resource_ptr << std::endl;
        } else {
            throw "Worker::doWork I have no resource to work on";
        }
    }
};

void do_something(const std::shared_ptr<Resource>& r)
{
    if (r) {
        std::cout << "do_something(" << *r << ")" << std::endl;
        std::cout << r->magic_number() << std::endl;
    }
}

int main()
{
    Worker w;
    auto r = std::make_shared<Resource>("vram");
    w.resource_ptr = r;

    do_something(r);
    r = nullptr;
    w.do_work();
    w.resource_ptr = nullptr;

    if (r)
        std::cout << " " << r->magic_number() << std::endl;
}
