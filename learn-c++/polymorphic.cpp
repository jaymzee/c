#include <iostream>
#include <memory>

// Most classes should not directly handle resources, but instead use
// members that perform resource handling for them.
//  - for memory it can be unique_ptr, share_ptr, vector, etc.
//  - for files it can be ofstream, ifstream
// Classes that avoid handling resources don't need to define any of the
// special member functions required to properly handle resources
//
// Rule of Zero
//
// However for the base class of a polymorphic hierarchy, the destructor
// should be declared public and virtual. This blocks implicit moves (and
// deprecates implicit copies), and so the special member functions have
// to be defaulted, however this makes the class prone to slicing, which is
// why polymorphic classes often define copy as deleted.
// A polymorphic class should suppress copying, which leads to the following
// generic wording for the Rule of Five:
//
// If you define or =delete any default operation, define or =delete them all.
//
class Base {
protected:
    virtual ~Base() = default;
public:
    Base() {}
    Base(const Base&) = delete;
    Base& operator=(const Base&) = delete;
    virtual void doSomething() {}
};

class Student : public Base {
    std::string name;
    int age;
public:
    Student(const std::string name, int age) :
        name(std::move(name)), age(age) {}
    friend std::ostream& operator<<(std::ostream& os, const Student& p);
};

std::ostream& operator<<(std::ostream& os, const Student& p)
{
    os << "{ name: " << p.name << ", age: " << p.age << " }";
    return os;
}

int main(int argc, char *argv[])
{
    auto s = std::make_unique<Student>("joe", 42);

    std::cout << *s << std::endl;

    return 0;
}

