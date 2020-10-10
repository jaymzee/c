#include <iostream>

int main()
{
    std::string s1 = "C makes it easy to shoot yourself in the foot; C++ makes it harder, "
                     "but when you do it blows your whole leg off.";
    std::cout << "s1 = " << '"' << s1 << '"' << (void *)s1.data() << std::endl;
    std::string s2 = std::move(s1);
    std::cout << "s2 = std::move(s1)\n";
    std::cout << "s1 = " << '"' << s1 << '"' << (void *)s1.data() << std::endl;
    std::cout << "s2 = " << '"' << s2 << '"' << (void *)s2.data() << std::endl;
}
