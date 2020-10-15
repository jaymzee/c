#include <iostream>
#include "../../snitch/Snitch.h"

class Person : Snitch {
public:
    int num;
public:
    Person(int num) : num(num), Snitch(num) {}
};

std::ostream& operator<<(std::ostream& os, const Person& a) {
    os << a.num;
    return os;
}

template <class T>
T sum(const T& a, const T& b)
{
    return a + b;
}

template <class T>
T sum(const T& a, const T& b, const T& c)
{
    return a + b + c;
}

template <>
Person sum<Person>(const Person& a, const Person& b)
{
    return Person(a.num + b.num);
}

template <>
Person sum<Person>(const Person& a, const Person& b, const Person& c)
{
    return Person(a.num + b.num + c.num);
}

template <class T>
T square(const T &x)
{
    return x * x;
}

template <>
Person square<Person>(const Person& a)
{
    return Person(a.num * a.num);
}

template <class FT, class T>
auto call(const char *fname, FT f, T&& x)
{
    std::cout << "calling " << fname << '(' << x << ')';
    auto y = f(std::forward<T>(x));
    std::cout << " = " << y << std::endl;
}

template <class FT, class A, class B>
auto call(const char *fname, FT f, A&& a, B&& b)
{
    std::cout << "calling " << fname << '(' << a << ", " << b << ')';
    auto c = f(std::forward<A>(a), std::forward<B>(b));
    std::cout << " = " << c << std::endl;
    return c;
}

template <class FT, class A, class B, class C>
auto call(const char *fname, FT f, A&& a, B&& b, C&& c)
{
    std::cout << "calling " << fname
              << '(' << a << ", " << b << ", " << c << ')';
    auto d = f(std::forward<A>(a),
               std::forward<B>(b),
               std::forward<C>(c));
    std::cout << " = " << d << std::endl;
    return d;
}

int main()
{
    Snitch::disable_log();
    {
        int ix = 2, iy = 3;
        Person a(42);

        //since sum is overloaded, we need to do the following
        //get function pointers to the overloads we want
        int (*sum2i)(const int&, const int&) = sum;
        Person (*sum2p)(const Person&, const Person&) = sum;
        Person (*sum3p)(const Person&, const Person&, const Person&) = sum;

        call("square<int>", square<int>, ix);
        call("square<int>", square<int>, 9);
        call("sum<int>", sum2i, ix, iy);
        call("sum<int>", sum2i, ix, 4);
        call("sum<int>", sum2i, 5, iy);
        call("sum<int>", sum2i, 6, 7);
        call("square<float>", square<float>, 5);
        call("square<Person>", square<Person>, a);
        call("sum<Person>", sum2p, Person(3), Person(4));
        call("sum<Person>", sum2p, a, Person(4));
        call("sum<Person>", sum3p, Person(3), Person(4), Person(5));
    }
    Snitch::enable_log();
    {
        Person a(42);
        call("square<Person>", square<Person>, a);
    }
    Snitch::disable_log();
}
