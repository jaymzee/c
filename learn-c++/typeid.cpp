#include <iostream>

int main()
{
    char c;
    short s;
    int i;
    long l;
    long long x;
    unsigned char h;
    unsigned short t;
    unsigned int j;
    unsigned long m;
    unsigned long long y;

    std::cout << typeid(c).name() << ' ' << sizeof(c) << std::endl;
    std::cout << typeid(s).name() << ' ' << sizeof(s) << std::endl;
    std::cout << typeid(i).name() << ' ' << sizeof(i) << std::endl;
    std::cout << typeid(l).name() << ' ' << sizeof(l) << std::endl;
    std::cout << typeid(x).name() << ' ' << sizeof(x) << std::endl;
    std::cout << typeid(h).name() << ' ' << sizeof(h) << std::endl;
    std::cout << typeid(t).name() << ' ' << sizeof(t) << std::endl;
    std::cout << typeid(j).name() << ' ' << sizeof(j) << std::endl;
    std::cout << typeid(m).name() << ' ' << sizeof(m) << std::endl;
    std::cout << typeid(y).name() << ' ' << sizeof(y) << std::endl;
}
