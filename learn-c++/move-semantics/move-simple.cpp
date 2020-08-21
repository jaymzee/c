#include <iostream>
#include <string>

class Person {
    std::string _name;
public:
    explicit Person(std::string name) noexcept : _name(std::move(name)) {}
    std::string Name() const { return _name; }
};

int main()
{
    Person p = Person("George");
    std::cout << p.Name() << std::endl;
}
