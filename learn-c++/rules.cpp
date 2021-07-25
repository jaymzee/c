#include <iostream>

template <class T>
class Foo {
public:
    Foo(T val) : num(val) {}
    T num;
};

template <class T> constexpr
const T& max(const T& a, const T& b) { return a > b ? a : b; }

template <class T> constexpr
const T& min(const T& a, const T& b) { return a < b ? a : b; }

class Student {
    int _age;
public:
    Student(int age) : _age(age) { }
    Student(const Student&) = default;
    Student& operator =(const Student&) = default;
    int age(void) { return _age; }
    void set_age(int age) { this->_age = age; }
};

int main()
{
    Student s{42};
    Student t{s};

    Foo<int> i{8};
    Foo<double> f{3.2};

    std::string n1{"joe"};
    std::string n2{"george"};

    printf("hello world!\n");
    printf("age: %d\n", s.age());
    printf("age: %d\n", t.age());
    printf("num: %d\n", i.num);
    printf("num: %f\n", f.num);
    printf("%d\n", max(2, 3));
    printf("%f\n", max(2.1, 3.2));
    printf("%d\n", min(2, 3));
    printf("%f\n", min(2.1, 3.2));
    printf("%s\n", ::min(n1, n2).c_str());
    printf("%s\n", ::max(n1, n2).c_str());
}
